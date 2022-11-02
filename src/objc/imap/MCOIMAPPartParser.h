//
//  MCOIMAPPartParser.h
//  mailcore2
//
//  Created by luzhixin on 2022/10/10.
//  Copyright © 2022 MailCore. All rights reserved.
//

#ifndef MCOIMAPPartParser_h
#define MCOIMAPPartParser_h

#import <Foundation/Foundation.h>

@class MCOAbstractMessage;

@interface MCOIMAPPartParser : NSObject

+ (void) parseMessage:(MCOAbstractMessage *)message
            htmlParts:(NSMutableArray *)htmlParts
           plainParts:(NSMutableArray *)plainParts
          attachments:(NSMutableArray *)attachments
    inlineAttachments:(NSMutableArray *)inlineAttachments;

@end

#endif /* MCOIMAPPartParser_h */
