//
//  MCOIMAPPart.h
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/23/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#ifndef MAILCORE_MCOIMAPABSTRACTPART_H

#define MAILCORE_MCOIMAPABSTRACTPART_H

#import <MailCore/MCOAbstractPart.h>

#import <MailCore/MCOConstants.h>

/** Represents a single IMAP message part */

@interface MCOIMAPPart : MCOAbstractPart <NSCoding>

@end

#endif
