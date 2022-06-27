//
//  MCOSMTPSyncSession.h
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/29/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#ifndef MAILCORE_MCOSMTPSYNCSESSION_H

#define MAILCORE_MCOSMTPSYNCSESSION_H

#import <Foundation/Foundation.h>

#import <MailCore/MCOConstants.h>

/** 
 This class is used to create an SMTP connection and send messages

 After calling a method that returns an operation you must call start: on the instance
 to begin the operation.
*/


@class MCOAddress;

@interface MCOSMTPSyncSession : NSObject

/** This is the hostname of the SMTP server to connect to. */
@property (nonatomic, copy) NSString * hostname;

/** This is the port of the SMTP server to connect to. */
@property (nonatomic, assign) unsigned int port;

/** This is the username of the account. */
@property (nonatomic, copy) NSString * username;

/** This is the password of the account. */
@property (nonatomic, copy) NSString * password;

/** This is the OAuth2 token. */
@property (nonatomic, copy) NSString *OAuth2Token;

/** 
 This is the authentication type to use to connect.
 `MCOAuthTypeSASLNone` means that it uses the clear-text is used (and is the default).
 @warning *Important*: Over an encrypted connection like TLS, the password will still be secure
*/
@property (nonatomic, assign) MCOAuthType authType;

/**
 This is the encryption type to use.
 See MCOConnectionType for more information.
*/
@property (nonatomic, assign) MCOConnectionType connectionType;

/** This is the timeout of the connection. */
@property (nonatomic, assign) NSTimeInterval timeout;

/** When set to YES, the connection will fail if the certificate is incorrect. */
@property (nonatomic, assign, getter=isCheckCertificateEnabled) BOOL checkCertificateEnabled;

/**
 If set to YES, when sending the EHLO or HELO command, use IP address instead of hostname.
 Default is NO.
*/
@property (nonatomic, assign, getter=isUseHeloIPEnabled) BOOL useHeloIPEnabled;

/**
 Sets logger callback. The network traffic will be sent to this block.
 
 [session setConnectionLogger:^(void * connectionID, MCOConnectionLogType type, NSData * data) {
   ...
 }];
 */
@property (nonatomic, copy) MCOConnectionLogger connectionLogger;


- (MCOErrorCode) loginIfNeeded; //Not used

- (NSString*) lastSMTPResponse; //Not used

- (MCOErrorCode) lastSMTPResponseCode; //Not used

- (MCOErrorCode) connect;
   
- (void) disconnect;

@end

#endif
