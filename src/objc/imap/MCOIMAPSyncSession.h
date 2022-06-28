//
//  MCOIMAPSession.h
//  mailcore2
//
//  Created by Matt Ronge on 1/31/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#ifndef MAILCORE_MCOIMAPSYNCSESSION_H

#define MAILCORE_MCOIMAPSYNCSESSION_H

#import <Foundation/Foundation.h>
#import <MailCore/MCOConstants.h>


@class MCOIMAPOperation;
@class MCOIMAPNamespace;
@class MCOIMAPIdentity;

/**
 This is the main IMAP class from which all operations are created

 After calling a method that returns an operation you must call start: on the instance
 to begin the operation.
*/

@interface MCOIMAPSyncSession : NSObject

/** This is the hostname of the IMAP server to connect to. */
@property (nonatomic, copy) NSString *hostname;

/** This is the port of the IMAP server to connect to. */
@property (nonatomic, assign) unsigned int port;

/** This is the username of the account. */
@property (nonatomic, copy) NSString *username;

/** This is the password of the account. */
@property (nonatomic, copy) NSString *password;

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

/** When set to YES, VoIP capability will be enabled on the IMAP connection on iOS */
@property (nonatomic, assign, getter=isVoIPEnabled) BOOL voIPEnabled;


/** The default namespace. */
@property (nonatomic, strong) MCOIMAPNamespace * defaultNamespace;

/** The identity of the IMAP client. */
@property (nonatomic, copy) MCOIMAPIdentity * clientIdentity;

/** The identity of the IMAP server. */
@property (nonatomic, strong, readonly) MCOIMAPIdentity * serverIdentity;

/**
 Display name of the Gmail user. It will be nil if it's not a Gmail server.

 ** DEPRECATED **
 This attribute has been broken by Gmail IMAP server. It's not longer available
 as a correct display name.
*/
@property (nonatomic, copy, readonly) NSString * gmailUserDisplayName DEPRECATED_ATTRIBUTE;

@property (nonatomic, assign, readonly, getter=isIdleEnabled) BOOL idleEnabled;


/**
 Sets logger callback. The network traffic will be sent to this block.

 [session setConnectionLogger:^(void * connectionID, MCOConnectionLogType type, NSData * data) {
    NSLog(@"%@", [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease]);
    // ...
 }];
*/
@property (nonatomic, copy) MCOConnectionLogger connectionLogger;

/** This property provides some hints to MCOIMAPSession about where it's called from.
 It will make MCOIMAPSession safe. It will also set all the callbacks of operations to run on this given queue.
 Defaults to the main queue.
 This property should be used only if there's performance issue using MCOIMAPSession in the main thread. */

/** This is the timeout of the connection. */

- (MCOErrorCode) getErrorCode; //not used

- (NSString*) loginResponse; //not used

- (MCOErrorCode) login; //not used

- (MCOErrorCode) loginIfNeeded; //not used

- (MCOErrorCode) connect;
                         
- (void) disconnect;

@end

#endif
