//
//  MCOIMAPCheckAccount.cpp
//  mailcore2
//
//  Created by andy on 15/12/11.
//  Copyright © 2015年 MailCore. All rights reserved.
//

#import "MCOIMAPCheckAccountOperation.h"

#include "MCAsyncIMAP.h"
#include "MCIMAPCheckAccountOperation.h"

#import "MCOOperation+Private.h"
#import "MCOUtils.h"


typedef void (^CompletionType)(NSError *error, NSString * response);

@implementation MCOIMAPCheckAccountOperation {
    CompletionType _completionBlock;
}

#define nativeType mailcore::IMAPCheckAccountOperation

+ (void) load
{
    MCORegisterClass(self, &typeid(nativeType));
}

+ (NSObject *) mco_objectWithMCObject:(mailcore::Object *)object
{
    nativeType * op = (nativeType *) object;
    return [[[self alloc] initWithMCOperation:op] autorelease];
}

- (void) dealloc
{
    [_completionBlock release];
    [super dealloc];
}

- (void)start:(void (^)(NSError * error, NSString * info))completionBlock
{
    _completionBlock = [completionBlock copy];
    [self start];
}

- (void) cancel
{
    [_completionBlock release];
    _completionBlock = nil;
    [super cancel];
}

- (void) operationCompleted
{
    if (_completionBlock == NULL)
        return;
    
    nativeType *op = MCO_NATIVE_INSTANCE;
    NSString *response = [NSString mco_stringWithMCString:op->getLoginResponse()];
    if (op->error() == mailcore::ErrorNone) {
        _completionBlock(nil, response);
    } else {
        NSError *error = [NSError mco_errorWithErrorCode:op->error()];
        _completionBlock(error, response);
    }
    
    [_completionBlock release];
    _completionBlock = nil;
}

@end