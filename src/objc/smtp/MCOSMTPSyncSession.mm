//
//  MCOSMTPSyncSession.m
//  mailcore2
//
//  Created by Youbing Yang on 6/24/2022.
//  Copyright (c) 2013 MailCore. All rights reserved.
//


#import "MCOSMTPSyncSession.h"
#import "MCOUtils.h"
#import "MCOSMTPOperation.h"
#import "MCOOperation+Private.h"
#import "MCOAddress.h"
#import "MCOSMTPOperation+Private.h"
#include "MCSMTPSession.h"


using namespace mailcore;

@interface MCOSMTPSyncSession ()



@end

class MCOSMTPSyncSessionLogger : public Object, public ConnectionLogger {
public:
    MCOSMTPSyncSessionLogger(MCOConnectionLogger connLogger)
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

@implementation MCOSMTPSyncSession {
    mailcore::SMTPSession * _session;
    MCOConnectionLogger _connectionLogger;
    MCOSMTPSyncSessionLogger * _loggerBridge;
}

#define nativeType mailcore::SMTPSession

- (mailcore::Object *) mco_mcObject
{
    return _session;
}

- (instancetype) init {
    self = [super init];
    
    _session = new mailcore::SMTPSession();
    
    _connectionLogger = NULL;
    _loggerBridge = NULL;
    
    return self;
}

- (void)dealloc {
    MC_SAFE_RELEASE(_loggerBridge);
    [_connectionLogger release];
    _session->setConnectionLogger(NULL);
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
MCO_OBJC_SYNTHESIZE_BOOL(setUseHeloIPEnabled, useHeloIPEnabled)


- (void) setConnectionLogger:(MCOConnectionLogger)connectionLogger
{
    [_connectionLogger release];
    _connectionLogger = [connectionLogger copy];
    
    if (_connectionLogger != nil) {
        _loggerBridge = new MCOSMTPSyncSessionLogger(connectionLogger);
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


- (MCOErrorCode) loginIfNeeded {
    ErrorCode errCode = ErrorNone;
    
    _session->loginIfNeeded(&errCode);
    
    return (MCOErrorCode)errCode;
}


- (NSString*) lastSMTPResponse {
    return [NSObject mco_objectWithMCObject:((mailcore::SMTPSession *) _session)->lastSMTPResponse()];
}

- (MCOErrorCode) lastSMTPResponseCode {
    int code = _session->lastSMTPResponseCode();
    return (MCOErrorCode)code;
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
