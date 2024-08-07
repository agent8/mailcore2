//
//  IMAPAsyncConnection.cc
//  mailcore2
//
//  Created by DINH Viêt Hoà on 1/12/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#include "MCIMAPAsyncConnection.h"

#include "MCIMAP.h"
#include "MCIMAPFolderInfoOperation.h"
#include "MCIMAPFolderStatusOperation.h"
#include "MCIMAPFetchFoldersOperation.h"
#include "MCIMAPRenameFolderOperation.h"
#include "MCIMAPDeleteFolderOperation.h"
#include "MCIMAPCreateFolderOperation.h"
#include "MCIMAPSubscribeFolderOperation.h"
#include "MCIMAPExpungeOperation.h"
#include "MCIMAPAppendMessageOperation.h"
#include "MCIMAPCopyMessagesOperation.h"
#include "MCIMAPFetchMessagesOperation.h"
#include "MCIMAPFetchContentOperation.h"
#include "MCIMAPFetchContentToFileOperation.h"
#include "MCIMAPFetchParsedContentOperation.h"
#include "MCIMAPStoreFlagsOperation.h"
#include "MCIMAPStoreLabelsOperation.h"
#include "MCIMAPSearchOperation.h"
#include "MCIMAPConnectOperation.h"
#include "MCIMAPCheckAccountOperation.h"
#include "MCIMAPFetchNamespaceOperation.h"
#include "MCIMAPIdleOperation.h"
#include "MCIMAPIdentityOperation.h"
#include "MCIMAPCapabilityOperation.h"
#include "MCIMAPQuotaOperation.h"
#include "MCOperationQueueCallback.h"
#include "MCIMAPDisconnectOperation.h"
#include "MCIMAPNoopOperation.h"
#include "MCIMAPAsyncSession.h"
#include "MCConnectionLogger.h"
#include "MCIMAPMessageRenderingOperation.h"
#include "MCIMAPCustomCommandOperation.h"
#include "MCIMAPIdentity.h"
#include "MCMessageConstants.h"

using namespace mailcore;

namespace mailcore {

    class IMAPOperationQueueCallback : public Object, public OperationQueueCallback {
    public:
        IMAPOperationQueueCallback(IMAPAsyncConnection * connection) {
            mConnection = connection;
        }

        virtual ~IMAPOperationQueueCallback() {
        }

        virtual void queueStartRunning() {
            mConnection->setQueueRunning(true);
            if (mConnection->owner()) {
                mConnection->owner()->operationRunningStateChanged();
            }
            mConnection->queueStartRunning();
        }

        virtual void queueStoppedRunning() {
            mConnection->setQueueRunning(false);
            mConnection->tryAutomaticDisconnect();
            if (mConnection->owner()) {
                mConnection->owner()->operationRunningStateChanged();
            }
            mConnection->queueStoppedRunning();
        }

    private:
        IMAPAsyncConnection * mConnection;
    };

    class IMAPConnectionLogger : public Object, public ConnectionLogger {
    public:
        IMAPConnectionLogger(IMAPAsyncConnection * connection) {
            mConnection = connection;
        }

        virtual ~IMAPConnectionLogger() {
        }

        virtual void log(void * sender, ConnectionLogType logType, Data * buffer)
        {
            mConnection->logConnection(logType, buffer);
        }

    private:
        IMAPAsyncConnection * mConnection;
    };

    class IMAPNoopOperationCallback:public Object, public OperationCallback{
    public:
        IMAPNoopOperationCallback(IMAPAsyncConnection * context){
            this->context = context;
        }
        virtual void operationFinished(Operation * op){
            IMAPOperation * operation = (IMAPOperation*)op;
            if(context->noopError == operation->error()){
                context->noopRepeatCount++;
            }else{
                context->noopRepeatCount = 0;
            }
            context->noopError = operation->error();
        }
    private:
        IMAPAsyncConnection * context;
    };
}
static int connectionCount = 0;
IMAPAsyncConnection::IMAPAsyncConnection()
{
    mSession = new IMAPSession();
    mQueue = new OperationQueue();
    mDefaultNamespace = NULL;
    mClientIdentity = new IMAPIdentity();
    mLastFolder = NULL;
    mQueueCallback = new IMAPOperationQueueCallback(this);
    mNoopCallback = new IMAPNoopOperationCallback(this);
    mQueue->setCallback(mQueueCallback);
    mOwner = NULL;
    mConnectionLogger = NULL;
    pthread_mutex_init(&mConnectionLoggerLock, NULL);
    mInternalLogger = new IMAPConnectionLogger(this);
    mAutomaticConfigurationEnabled = true;
    mQueueRunning = false;
    mScheduledAutomaticDisconnect = false;
    MCLog("!!!!!New Connection.%d",++connectionCount);
}

IMAPAsyncConnection::~IMAPAsyncConnection()
{
    MCLog("!!!!!Free Connection.%d",--connectionCount);
#if __APPLE__
    cancelDelayedPerformMethodOnDispatchQueue((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL, dispatchQueue());
#else
    cancelDelayedPerformMethod((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL);
#endif
    pthread_mutex_destroy(&mConnectionLoggerLock);
    MC_SAFE_RELEASE(mInternalLogger);
    MC_SAFE_RELEASE(mQueueCallback);
    MC_SAFE_RELEASE(mNoopCallback);
    MC_SAFE_RELEASE(mLastFolder);
    MC_SAFE_RELEASE(mClientIdentity);
    MC_SAFE_RELEASE(mDefaultNamespace);
    MC_SAFE_RELEASE(mQueue);
    MC_SAFE_RELEASE(mSession);
}

void IMAPAsyncConnection::setHostname(String * hostname)
{
    mSession->setHostname(hostname);
}

String * IMAPAsyncConnection::hostname()
{
    return mSession->hostname();
}

void IMAPAsyncConnection::setPort(unsigned int port)
{
    mSession->setPort(port);
}

unsigned int IMAPAsyncConnection::port()
{
    return mSession->port();
}

void IMAPAsyncConnection::setUsername(String * username)
{
    mSession->setUsername(username);
}

String * IMAPAsyncConnection::username()
{
    return mSession->username();
}

void IMAPAsyncConnection::setPassword(String * password)
{
    mSession->setPassword(password);
}

String * IMAPAsyncConnection::password()
{
    return mSession->password();
}

void IMAPAsyncConnection::setOAuth2Token(String * token)
{
    mSession->setOAuth2Token(token);
}

String * IMAPAsyncConnection::OAuth2Token()
{
    return mSession->OAuth2Token();
}

void IMAPAsyncConnection::setAuthType(AuthType authType)
{
    mSession->setAuthType(authType);
}

AuthType IMAPAsyncConnection::authType()
{
    return mSession->authType();
}

void IMAPAsyncConnection::setConnectionType(ConnectionType connectionType)
{
    mSession->setConnectionType(connectionType);
}

ConnectionType IMAPAsyncConnection::connectionType()
{
    return mSession->connectionType();
}

void IMAPAsyncConnection::setTimeout(time_t timeout)
{
    mSession->setTimeout(timeout);
}

time_t IMAPAsyncConnection::timeout()
{
    return mSession->timeout();
}

void IMAPAsyncConnection::setCheckCertificateEnabled(bool enabled)
{
    mSession->setCheckCertificateEnabled(enabled);
}

bool IMAPAsyncConnection::isCheckCertificateEnabled()
{
    return mSession->isCheckCertificateEnabled();
}

void IMAPAsyncConnection::setVoIPEnabled(bool enabled)
{
    mSession->setVoIPEnabled(enabled);
}

bool IMAPAsyncConnection::isVoIPEnabled()
{
    return mSession->isVoIPEnabled();
}

void IMAPAsyncConnection::setDefaultNamespace(IMAPNamespace * ns)
{
    mSession->setDefaultNamespace(ns);
    MC_SAFE_REPLACE_RETAIN(IMAPNamespace, mDefaultNamespace, ns);
}

IMAPNamespace * IMAPAsyncConnection::defaultNamespace()
{
    return mDefaultNamespace;
}

void IMAPAsyncConnection::setClientIdentity(IMAPIdentity * identity)
{
    MC_SAFE_REPLACE_COPY(IMAPIdentity, mClientIdentity, identity);
    mSession->clientIdentity()->removeAllInfos();
    if (identity != NULL) {
        mc_foreacharray(String, key, identity->allInfoKeys()) {
            mSession->clientIdentity()->setInfoForKey(key, identity->infoForKey(key));
        }
    }
}

IMAPIdentity * IMAPAsyncConnection::clientIdentity()
{
    return mClientIdentity;
}

IMAPOperation * IMAPAsyncConnection::disconnectOperation()
{
    IMAPDisconnectOperation * op = new IMAPDisconnectOperation();
    op->setSession(this);
    op->autorelease();
    return op;
}

IMAPSession * IMAPAsyncConnection::session()
{
    return mSession;
}

unsigned int IMAPAsyncConnection::operationsCount()
{
#if MCO_KEEP_ALIVE
    return mQueue->countWithoutNoop();
#else
    return mQueue->count();
#endif
}

void IMAPAsyncConnection::cancelAllOperations()
{
    mQueue->cancelAllOperations();
}

void IMAPAsyncConnection::runOperation(IMAPOperation * operation)
{
    if (mScheduledAutomaticDisconnect) {
#if __APPLE__
        cancelDelayedPerformMethodOnDispatchQueue((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL, dispatchQueue());
#else
        cancelDelayedPerformMethod((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL);
#endif
        mOwner->release();
        mScheduledAutomaticDisconnect = false;
    }
    noopRepeatCount  = 0;
    mQueue->addOperation(operation);
}

void IMAPAsyncConnection::tryAutomaticDisconnect()
{
    // It's safe since no thread is running when this function is called.
    if (mSession->isDisconnected()) {
        return;
    }

    bool scheduledAutomaticDisconnect = mScheduledAutomaticDisconnect;
    if (scheduledAutomaticDisconnect) {
#if __APPLE__
        cancelDelayedPerformMethodOnDispatchQueue((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL, dispatchQueue());
#else
        cancelDelayedPerformMethod((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL);
#endif
    }

    mOwner->retain();
    mScheduledAutomaticDisconnect = true;
#if __APPLE__
    performMethodOnDispatchQueueAfterDelay((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL, dispatchQueue(), 30);
#else
    performMethodAfterDelay((Object::Method) &IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay, NULL, 30);
#endif

    if (scheduledAutomaticDisconnect) {
        mOwner->release();
    }
}

#if MCO_KEEP_ALIVE
void IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay(void * context)
{
    mScheduledAutomaticDisconnect = false;
    //NOTE: if error(except network) happens then stop noop
    if (mOwner->keepSessionAliveState() > 0 &&
            ((noopError == ErrorNone && noopRepeatCount < 72)/*noop 72 times (30 mins) before disconect*/
             || (noopError == ErrorConnection && noopRepeatCount < 10)/*retry 10 times if network error before disconect*/
            )
        ){
        //Weicheng: does need to keep all session or just the [Gmail]/All Mail and INBOX
        //modified by yyb: "[Gmail]/All Mail" is different in different language
        if (this->lastFolder() != NULL && (mLastFolder->isEqual(MCSTR("[Gmail]/All Mail")) || mLastFolder->isEqual(MCSTR("INBOX"))) || mLastFolderFlag == mailcore::IMAPFolderFlagAllMail){
            MCLog("keep session(%s) from disconnecting %d times with error:%d\n",this->lastFolder()->UTF8Characters(), noopRepeatCount, noopError);
            IMAPOperation * op = owner()->noopOperation();
            op->setCallback(mNoopCallback);
            op->setSession(this);
            mQueue->addOperation(op);
            return;
        }
    }
    if (noopError != ErrorNone){
        MCLog("Stop noop for there is an error:%d",this->noopError);
    }
    IMAPOperation * op = disconnectOperation();
    op->start();
    mOwner->release();
}
#else
void IMAPAsyncConnection::tryAutomaticDisconnectAfterDelay(void * context)
{
    mScheduledAutomaticDisconnect = false;
    
    IMAPOperation * op = disconnectOperation();
    op->start();
    
    mOwner->release();
}

#endif
void IMAPAsyncConnection::queueStartRunning()
{
    this->retain();
    mOwner->retain();
}

void IMAPAsyncConnection::queueStoppedRunning()
{
    mOwner->release();
    this->release();
}

void IMAPAsyncConnection::setLastFolder(String * folder)
{
    MC_SAFE_REPLACE_COPY(String, mLastFolder, folder);
}

String * IMAPAsyncConnection::lastFolder()
{
    return mLastFolder;
}

//added by yyb:
void IMAPAsyncConnection::setLastFolderFlag(mailcore::IMAPFolderFlag flag) {
    this->mLastFolderFlag = flag;
}

mailcore::IMAPFolderFlag IMAPAsyncConnection::lastFolderFlag() {
    return mLastFolderFlag;
}

void IMAPAsyncConnection::setOwner(IMAPAsyncSession * owner)
{
    mOwner = owner;
}

IMAPAsyncSession * IMAPAsyncConnection::owner()
{
    return mOwner;
}

void IMAPAsyncConnection::setConnectionLogger(ConnectionLogger * logger)
{
    pthread_mutex_lock(&mConnectionLoggerLock);
    mConnectionLogger = logger;
    pthread_mutex_unlock(&mConnectionLoggerLock);
    if (logger != NULL) {
        mSession->setConnectionLogger(mInternalLogger);
    }
    else {
        mSession->setConnectionLogger(NULL);
    }
}

ConnectionLogger * IMAPAsyncConnection::connectionLogger()
{
    ConnectionLogger * result;

    pthread_mutex_lock(&mConnectionLoggerLock);
    result = mConnectionLogger;
    pthread_mutex_unlock(&mConnectionLoggerLock);

    return result;
}

void IMAPAsyncConnection::logConnection(ConnectionLogType logType, Data * buffer)
{
    pthread_mutex_lock(&mConnectionLoggerLock);
    if (mConnectionLogger != NULL) {
        mConnectionLogger->log(this, logType, buffer);
    }
    pthread_mutex_unlock(&mConnectionLoggerLock);
}

void IMAPAsyncConnection::setAutomaticConfigurationEnabled(bool enabled)
{
    mAutomaticConfigurationEnabled = enabled;
    mSession->setAutomaticConfigurationEnabled(enabled);
}

bool IMAPAsyncConnection::isAutomaticConfigurationEnabled()
{
    return mAutomaticConfigurationEnabled;
}

bool IMAPAsyncConnection::isQueueRunning()
{
    return mQueueRunning;
}

void IMAPAsyncConnection::setQueueRunning(bool running)
{
    mQueueRunning = running;
}

#if __APPLE__
void IMAPAsyncConnection::setDispatchQueue(dispatch_queue_t dispatchQueue)
{
    mQueue->setDispatchQueue(dispatchQueue);
}

dispatch_queue_t IMAPAsyncConnection::dispatchQueue()
{
    return mQueue->dispatchQueue();
}
#endif
