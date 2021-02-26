//
//  MCIMAPPartParser.hpp
//  mailcore2
//
//  Created by weicheng qian on 2019/11/27.
//  Copyright © 2019 MailCore. All rights reserved.
//

#ifndef MCIMAPPartParser_h
#define MCIMAPPartParser_h
#include <MailCore/MCAbstract.h>
#include <MailCore/MCIMAP.h>
#include <MailCore/MCRFC822.h>

#include <stdio.h>
#ifdef __cplusplus
namespace mailcore {
    
    class MAILCORE_EXPORT IMAPPartParser {
    public:
        /**
           If need to parse rfc822 attachment, it needs to call parsePart with the rfc822 part.
         */
        static void parseMessage(AbstractMessage * message, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments);
        static AbstractMessage * parseMessage(String * filepath, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments);
        static void parsePart(AbstractPart * part, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments, String * defaultCharset);
        static void fixFilename(AbstractPart * part);
        static String * prettyPrint(AbstractMessage * message, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments);
    };
};
#endif
#endif /* MCIMAPPartParser_h */
