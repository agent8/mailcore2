//
//  MCOIMAPSyncSession.mm
//  mailcore2
//
//  Created by Matt Ronge on 1/31/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#import "MCOIMAPSyncSession.h"
#import "MCOObjectWrapper.h"
#import "MCOIMAPIdentity.h"
#import "MCOUtils.h"
#import "MCIMAPSession.h"
#import "MCIMAPIdentity.h"


using namespace mailcore;

@implementation MCOIMAPFetchMessageResult

- (instancetype) init {
    self = [super init];
    _errorCode = MCOErrorNone;
    _messages = nil;
    return self;
}

@end


@implementation MCOIMAPFolderStatusResult

- (instancetype) init {
    self = [super init];
    _errorCode = MCOErrorNone;
    _status = nil;
    return self;
}

@end

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
    
    _connectionLogger = NULL;
    _loggerBridge = NULL;
    
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

- (MCOErrorCode) select:(NSString *)folder {
    mailcore::String * mcFolder = [folder mco_mcString];
    ErrorCode mcError = ErrorNone;
    _session->select(mcFolder, &mcError);
    return (MCOErrorCode)mcError;
}

- (MCOErrorCode) selectIfNeeded:(NSString *)folder {
    mailcore::String * mcFolder = [folder mco_mcString];
    ErrorCode mcError = ErrorNone;
    _session->selectIfNeeded(mcFolder, &mcError);
    return (MCOErrorCode)mcError;
}

- (MCOIMAPFolderStatusResult *) folderStatus:(NSString *)folder {
    mailcore::String * mcFolder = [folder mco_mcString];
    ErrorCode mcError = ErrorNone;
    IMAPFolderStatus * mcFolderStatus = _session->folderStatus(mcFolder, &mcError);
    MCOIMAPFolderStatusResult * result = [MCOIMAPFolderStatusResult new];
    result.errorCode = (MCOErrorCode)mcError;
    result.status = MCO_TO_OBJC(mcFolderStatus);
    return result;
}

- (unsigned int) lastFolderMessageCount {
    return _session->lastFolderMessageCount();
}

- (MCOIMAPFetchMessageResult *) fetchMessagesByNumber:(MCOIndexSet *)numbers
                                               folder:(NSString *)folder
                                          requestKind:(MCOIMAPMessagesRequestKind)requestKind
                                               partID:(NSString *)partID
                                         extraHeaders:(NSArray *)extraHeaders
{
    mailcore::String * mcFolder = [folder mco_mcString];
    IMAPMessagesRequestKind mcRequestKind = (IMAPMessagesRequestKind) requestKind;
    mailcore::String * mcPartID = [partID mco_mcString];
    mailcore::IndexSet * mcNumbers = MCO_FROM_OBJC(mailcore::IndexSet, numbers);
    mailcore::Array * mcExtraHeaders = [extraHeaders mco_mcArray];
    mailcore::ErrorCode mcError = mailcore::ErrorNone;

    mailcore::Array * mcMessages = _session->fetchMessagesByNumberWithExtraHeaders(mcFolder, mcRequestKind, mcPartID, mcNumbers, NULL, mcExtraHeaders, &mcError);

    MCOIMAPFetchMessageResult * result = [MCOIMAPFetchMessageResult new];
    result.errorCode = (MCOErrorCode)mcError;
    result.messages = [NSArray mco_arrayWithMCArray:mcMessages];

    return result;
}

- (MCOIMAPFetchMessageResult *) fetchMessagesByUID:(MCOIndexSet *)uids
                                            folder:(NSString *)folder
                                       requestKind:(MCOIMAPMessagesRequestKind)requestKind
                                            partID:(NSString *)partID
                                      extraHeaders:(NSArray *)extraHeaders
{
    mailcore::String * mcFolder = [folder mco_mcString];
    IMAPMessagesRequestKind mcRequestKind = (IMAPMessagesRequestKind) requestKind;
    mailcore::String * mcPartID = [partID mco_mcString];
    mailcore::IndexSet * mcUids = MCO_FROM_OBJC(mailcore::IndexSet, uids);
    mailcore::Array * mcExtraHeaders = [extraHeaders mco_mcArray];
    mailcore::ErrorCode mcError = mailcore::ErrorNone;

    mailcore::Array * mcMessages = _session->fetchMessagesByUIDWithExtraHeaders(mcFolder, mcRequestKind, mcPartID, mcUids, NULL, mcExtraHeaders, &mcError);

    MCOIMAPFetchMessageResult * result = [MCOIMAPFetchMessageResult new];
    result.errorCode = (MCOErrorCode)mcError;
    result.messages = [NSArray mco_arrayWithMCArray:mcMessages];

    return result;
}

@end
