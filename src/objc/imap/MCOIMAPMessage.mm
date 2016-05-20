//
//  MCOIMAPMessage.m
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/23/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#import "MCOIMAPMessage.h"

#include "MCIMAP.h"

#import "MCOUtils.h"
#import "MCOAbstractMessageRendererCallback.h"
#import "MCOHTMLRendererDelegate.h"
#import "MCOHTMLRendererIMAPDelegate.h"
#import <MailCore/MCMessageConstants.h>
using namespace mailcore;
@implementation MCOIMAPMessage

#define nativeType mailcore::IMAPMessage

+ (void) load
{
    MCORegisterClass(self, &typeid(nativeType));
}

- (instancetype) init
{
    mailcore::IMAPMessage * msg = new mailcore::IMAPMessage();
    self = [self initWithMCMessage:msg];
    msg->release();
    return self;
}

+ (NSObject *) mco_objectWithMCObject:(mailcore::Object *)object
{
    mailcore::IMAPMessage * msg = (mailcore::IMAPMessage *) object;
    return [[[self alloc] initWithMCMessage:msg] autorelease];
}

MCO_SYNTHESIZE_NSCODING

MCO_OBJC_SYNTHESIZE_SCALAR(uint32_t, uint32_t, setUid, uid)
MCO_OBJC_SYNTHESIZE_SCALAR(uint32_t, uint32_t, setSequenceNumber, sequenceNumber)
MCO_OBJC_SYNTHESIZE_SCALAR(uint32_t, uint32_t, setSize, size)
MCO_OBJC_SYNTHESIZE_SCALAR(MCOMessageFlag, mailcore::MessageFlag, setFlags, flags)
MCO_OBJC_SYNTHESIZE_SCALAR(MCOMessageFlag, mailcore::MessageFlag, setOriginalFlags, originalFlags)
MCO_OBJC_SYNTHESIZE_ARRAY(setCustomFlags, customFlags)
MCO_OBJC_SYNTHESIZE_SCALAR(uint64_t, uint64_t, setModSeqValue, modSeqValue)
MCO_OBJC_SYNTHESIZE(AbstractPart, setMainPart, mainPart)
MCO_OBJC_SYNTHESIZE_ARRAY(setGmailLabels, gmailLabels)
MCO_OBJC_SYNTHESIZE_SCALAR(uint64_t, uint64_t, setGmailThreadID, gmailThreadID)
MCO_OBJC_SYNTHESIZE_SCALAR(uint64_t, uint64_t, setGmailMessageID, gmailMessageID)


- (NSData *)partData:(MCOEncoding) encoding{
    mailcore::Data * data = MCO_NATIVE_INSTANCE->partData();
    if (data != NULL) {
        data = data->decodedDataUsingEncoding((Encoding)encoding);
        return MCO_TO_OBJC(data);
    } else {
        return NULL;
    }
}

- (NSString *)decodePart:(MCOEncoding) encoding charset:(NSString *)charset isHTML:(BOOL) isHTML{
    mailcore::Data * data = MCO_NATIVE_INSTANCE->partData();
//    NSString * str1 = MCO_TO_OBJC(MCO_NATIVE_INSTANCE->decodePart(data, (Encoding)encoding, [charset mco_mcString], isHTML));
//    NSLog(@"S1:%@",str1);
    if (data != NULL){
        data = data->decodedDataUsingEncoding((Encoding)encoding);
        String * mcStr = data->stringWithDetectedCharset([charset mco_mcString], isHTML);
        NSString * str = MCO_TO_OBJC(mcStr);
        return str;
    } else {
        return NULL;
    }
}

- (MCOAbstractPart *) partForPartID:(NSString *)partID
{
    return MCO_TO_OBJC(MCO_NATIVE_INSTANCE->partForPartID([partID mco_mcString]));
}

- (NSString *) htmlRenderingWithFolder:(NSString *)folder
                              delegate:(id <MCOHTMLRendererIMAPDelegate>)delegate
{
    MCOAbstractMessageRendererCallback * htmlRenderCallback = new MCOAbstractMessageRendererCallback(self, delegate, delegate);
    NSString * result = MCO_TO_OBJC(MCO_NATIVE_INSTANCE->htmlRendering([folder mco_mcString], htmlRenderCallback, htmlRenderCallback));
    htmlRenderCallback->release();
    
    return result;
}

@end
