//
//  MCOIMAPSyncSession.mm
//  mailcore2
//
//  Created by Matt Ronge on 1/31/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#import "MCOIMAPSyncSession.h"


#import "MCOObjectWrapper.h"
#import "MCOIMAPMessageRenderingOperation.h"
#import "MCOIMAPIdentity.h"

#import "MCOUtils.h"

#import <MailCore/MCAsync.h>

#include "MCIMAPMessageRenderingOperation.h"


using namespace mailcore;

@interface MCOIMAPSyncSession ()


@end


class MCOIMAPSyncSessionLogger : public Object, public ConnectionLogger {
public:
    MCOIMAPSyncSessionLogger(MCOConnectionLogger connLogger)
    {
        mLogger = connLogger;
    }
    
    virtual void log(void * sender, ConnectionLogType logType, Data * data)
    {
        if (mLogger) {
            @autoreleasepool {
                //[mSession _logWithSender:sender connectionType:(MCOConnectionLogType)logType data:MCO_TO_OBJC(data)];                
                //_connectionLogger(sender, logType, data);
                mLogger(sender, (MCOConnectionLogType)logType, MCO_TO_OBJC(data));
            }
        }
    }
    
private:
    MCOConnectionLogger mLogger;
};



@implementation MCOIMAPSyncSession {
    ErrorCode mErrCode;
    IMAPSession * _session;
    MCOConnectionLogger _connectionLogger;
    MCOIMAPSyncSessionLogger * _loggerBridge;
}

#define nativeType mailcore::IMAPSession

- (mailcore::Object *) mco_mcObject
{
    return _session;
}

- (instancetype) init {
    self = [super init];
    
    _session = new IMAPSession();
    
    MCOConnectionLogger _connectionLogger;
    MCOIMAPSyncSessionLogger * _loggerBridge;
    
    mErrCode = ErrorNone;
    
    return self;
}

- (void)dealloc {
    MC_SAFE_RELEASE(_loggerBridge);
    _session->setConnectionLogger(NULL);

    [_connectionLogger release];
    _session->release();
    [super dealloc];
}

MCO_OBJC_SYNTHESIZE_STRING(setHostname, hostname)
MCO_OBJC_SYNTHESIZE_SCALAR(unsigned int, unsigned int, setPort, port)
MCO_OBJC_SYNTHESIZE_STRING(setUsername, username)
MCO_OBJC_SYNTHESIZE_STRING(setPassword, password)
MCO_OBJC_SYNTHESIZE_STRING(setOAuth2Token, OAuth2Token)
MCO_OBJC_SYNTHESIZE_SCALAR(MCOAuthType, mailcore::AuthType, setAuthType, authType)
MCO_OBJC_SYNTHESIZE_SCALAR(MCOConnectionType, mailcore::ConnectionType, setConnectionType, connectionType)
MCO_OBJC_SYNTHESIZE_SCALAR(NSTimeInterval, time_t, setTimeout, timeout)
MCO_OBJC_SYNTHESIZE_BOOL(setCheckCertificateEnabled, isCheckCertificateEnabled)
MCO_OBJC_SYNTHESIZE_BOOL(setVoIPEnabled, isVoIPEnabled)

- (MCOErrorCode) getErrorCode {
    return (MCOErrorCode)mErrCode;
}

- (NSString*) loginResponse {
    return [NSObject mco_objectWithMCObject:((mailcore::IMAPSession *) _session)->loginResponse()];
}

/*
- (NSString *) hostname {
    return [NSObject mco_objectWithMCObject:((mailcore::IMAPSession *) [self mco_mcObject])->hostname()];
}
 
- (void) setHostname:(NSString *)hostname {
    ((mailcore::IMAPSession *) [self mco_mcObject])->setHostname((mailcore::String *) [(hostname) mco_mcObject]);
}
*/

- (void) setDefaultNamespace:(MCOIMAPNamespace *)defaultNamespace
{
    _session->setDefaultNamespace(MCO_FROM_OBJC(IMAPNamespace, defaultNamespace));
}

- (MCOIMAPNamespace *) defaultNamespace
{
    return MCO_TO_OBJC(_session->defaultNamespace());
}

- (MCOIMAPIdentity *) clientIdentity
{
    return MCO_OBJC_BRIDGE_GET(clientIdentity);
}

- (void) setClientIdentity:(MCOIMAPIdentity *)clientIdentity
{
    MCO_OBJC_BRIDGE_SET(setClientIdentity, IMAPIdentity, clientIdentity);
}

- (MCOIMAPIdentity *) serverIdentity
{
    return MCO_OBJC_BRIDGE_GET(serverIdentity);
}

- (NSString *) gmailUserDisplayName
{
    return MCO_TO_OBJC(_session->gmailUserDisplayName());
}

- (BOOL) isIdleEnabled
{
    return MCO_NATIVE_INSTANCE->isIdleEnabled();
}

- (void) setConnectionLogger:(MCOConnectionLogger)connectionLogger
{
    [_connectionLogger release];
    _connectionLogger = [connectionLogger copy];
    
    if (_connectionLogger != nil) {
        _loggerBridge = new MCOIMAPSyncSessionLogger(connectionLogger);
        _session->setConnectionLogger(_loggerBridge);
    }
    else {
        _session->setConnectionLogger(NULL);
    }
}

- (MCOConnectionLogger) connectionLogger
{
    return _connectionLogger;
}


#pragma mark - Operations

- (MCOErrorCode) login {
    ErrorCode errCode = ErrorNone;
    
    _session->login(&errCode);
    
    return (MCOErrorCode)errCode;
}

- (MCOErrorCode) loginIfNeeded {
    ErrorCode errCode = ErrorNone;
    
    _session->loginIfNeeded(&errCode);
    
    return (MCOErrorCode)errCode;
}

- (MCOErrorCode) connect {
    ErrorCode errCode = ErrorNone;
    
    _session->connect(&errCode);
    
    return (MCOErrorCode)errCode;
}
                         
- (void) disconnect {
    _session->disconnect();
}


@end
