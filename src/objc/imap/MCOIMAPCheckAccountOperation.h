//
//  MCOIMAPCheckAccount.h
//  mailcore2
//
//  Created by andy on 15/12/11.
//  Copyright © 2015年 MailCore. All rights reserved.
//

#ifndef MAILCORE_MCOIMAPCHECKACCOUNTOPERATION_H

#define MAILCORE_MCOIMAPCHECKACCOUNTOPERATION_H

#import <MailCore/MCOIMAPBaseOperation.h>
#import <MailCore/MCOConstants.h>

NS_ASSUME_NONNULL_BEGIN
@interface MCOIMAPCheckAccountOperation : MCOIMAPBaseOperation

- (void) start:(void (^)(NSError * __nullable error, NSString * __nullable info))completionBlock;

@end
NS_ASSUME_NONNULL_END

#endif