//
//  MCOIMAPPartParser.mm
//  mailcore2
//
//  Created by luzhixin on 2022/10/10.
//  Copyright © 2022 MailCore. All rights reserved.
//

#import "MCOIMAPPartParser.h"
#import "MCOAbstractMessage.h"
#import "NSObject+MCO.h"

#include "MCIMAPPartParser.h"

@implementation MCOIMAPPartParser

+ (void) parseMessage:(MCOAbstractMessage *)message
            htmlParts:(NSMutableArray *)htmlParts
           plainParts:(NSMutableArray *)plainParts
          attachments:(NSMutableArray *)attachments
    inlineAttachments:(NSMutableArray *)inlineAttachments
{
    if (message == nil) {
        return;
    }

    mailcore::AbstractMessage * mcMessage = MCO_FROM_OBJC(mailcore::AbstractMessage, message);

    if (!mcMessage) {
        return;
    }

    mailcore::AutoreleasePool * pool = new mailcore::AutoreleasePool();

    mailcore::Array * mcHtmlParts = mailcore::Array::array();
    mailcore::Array * mcPlainParts = mailcore::Array::array();
    mailcore::Array * mcAttachments = mailcore::Array::array();
    mailcore::Array * mcInlineAttachments = mailcore::Array::array();

    mailcore::IMAPPartParser::parseMessage(mcMessage, mcHtmlParts, mcPlainParts, mcAttachments, mcInlineAttachments);

    if (htmlParts != nil) {
        for(unsigned int i = 0 ; i < mcHtmlParts->count() ; i++) {
            [htmlParts addObject:[NSObject mco_objectWithMCObject:mcHtmlParts->objectAtIndex(i)]];
        }
    }

    if (plainParts != nil) {
        for(unsigned int i = 0 ; i < mcPlainParts->count() ; i++) {
            [plainParts addObject:[NSObject mco_objectWithMCObject:mcPlainParts->objectAtIndex(i)]];
        }
    }

    if (attachments != nil) {
        for(unsigned int i = 0 ; i < mcAttachments->count() ; i++) {
            [attachments addObject:[NSObject mco_objectWithMCObject:mcAttachments->objectAtIndex(i)]];
        }
    }

    if (inlineAttachments != nil) {
        for(unsigned int i = 0 ; i < mcInlineAttachments->count() ; i++) {
            [inlineAttachments addObject:[NSObject mco_objectWithMCObject:mcInlineAttachments->objectAtIndex(i)]];
        }
    }

    pool->release();
}

@end
