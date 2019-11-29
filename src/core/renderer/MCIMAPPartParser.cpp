//
//  MCIMAPPartParser.cpp
//  mailcore2
//
//  Created by weicheng qian on 2019/11/27.
//  Copyright © 2019 MailCore. All rights reserved.
//

#include "MCIMAPPartParser.h"

using namespace mailcore;
static bool partContainsMimeType(AbstractPart * part, String * mimeType);

static bool canPreviewPart(AbstractPart * part) {
    String * mimeType = part->mimeType();
    String * filename = part->filename();
    // is mimetype start with image/ or filename endwith .jpg/.jpeg/.png/.gif, .etc.
    if (mimeType != NULL) {
        if (mimeType->lowercaseString()->hasPrefix(MCSTR("image/"))) {
            return true;
        }
    }
    if (filename != NULL) {
        if (filename->hasSuffix(MCSTR("./jpg")) || filename->hasSuffix(MCSTR("./jpeg")) ||
            filename->hasSuffix(MCSTR("./png")) || filename->hasSuffix(MCSTR("./gif"))) {
            return true;
        }
    }
    return false;
}
static bool isTextPart(AbstractPart * part)
{
    String * mimeType = part->mimeType();
    if (!part->isInlineAttachment()) {
        if (part->isAttachment() || part->filename() != NULL) {
            return false;
        }
    }
    if (MCSTR("text/plain")->isEqualCaseInsensitive(mimeType)) {
        return true;
    }
    else if (MCSTR("text/html")->isEqualCaseInsensitive(mimeType)) {
        return true;
    }
    else {
        return false;
    }
}
static bool partContainsMimeType(AbstractPart * part, String * mimeType)
{
    MCAssert(part != NULL);
    if (part->mimeType()->isEqualCaseInsensitive(mimeType)) {
        return true;
    }
    switch (part->partType()) {
        case PartTypeSingle:
            // return part->mimeType()->isEqualCaseInsensitive(mimeType);
            // Has compared at the head of this function.
            return false;
        case PartTypeMessage: {
            AbstractMessagePart * mainPart = (AbstractMessagePart *)part;
            return partContainsMimeType(mainPart->mainPart(), mimeType);
        }
        case PartTypeMultipartMixed:
        case PartTypeMultipartRelated:
        case PartTypeMultipartAlternative:
        case PartTypeMultipartSigned: {
            AbstractMultipart * multipart = (AbstractMultipart *)part;
            for(unsigned int i = 0 ; i < multipart->parts()->count() ; i ++) {
                AbstractPart * subpart = (AbstractPart *) multipart->parts()->objectAtIndex(i);
                if (partContainsMimeType(subpart, mimeType)) {
                    return true;
                }
            }
            return false;
        }
        default:
            return false;
    }
}

void IMAPPartParser::parsePart(AbstractPart * part, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments, String * defaultCharset){
    // https://tools.ietf.org/html/rfc2046
    // Note: Fill the fields(charset and mimetype). We DO NOT trust inline and attachment field from RFC822.
    String * charset = part->charset();
    if ((charset == NULL || charset == MCSTR("")) && defaultCharset != NULL) {
        part->setCharset(defaultCharset);
    }
    if (part->mimeType() == NULL) {
        part->setMimeType(MCSTR("application/octet-stream"));
    }
    switch (part->partType()) {
        case PartTypeSingle: {
            if (isTextPart(part)) {
                if (htmlParts != NULL) {
                    htmlParts->addObject(part);
                }
                if (plainParts != NULL) {
                    plainParts->addObject(part);
                }
            } else if (canPreviewPart(part)) {
                // We prefer to display an image into html body instead of attachments.
                if (htmlParts != NULL) {
                    htmlParts->addObject(part);
                }
                else if (attachments != NULL) {
                    attachments->addObject(part);
                    part->setAttachment(true);
                }
                // This is ONLY for the email that do not follow the RFC2387.
                // Adding irrelevant part into inlineattachments does not matter.
                if (inlineAttachments != NULL && part->contentID() != NULL && part->contentID() != MCSTR("")) {
                    inlineAttachments->addObject(part);
                    part->setInlineAttachment(true);
                }
            } else {
                if (attachments != NULL) {
                    attachments->addObject(part);
                    part->setAttachment(true);
                }
            }
            break;
        }
        case PartTypeMessage: {
            if (attachments != NULL) {
                attachments->addObject(part);
                part->setAttachment(true);
            }
            break;
        }
        case PartTypeMultipartRelated:{
            AbstractMultipart * multipart = (AbstractMultipart *)part;
            // RFC: https://tools.ietf.org/html/rfc2387
            // we need to find the root part, by default it is 0
            unsigned int rootIndex = 0;
            String * rootCid = multipart->contentTypeParameterValueForName(MCSTR("start"));
            for(unsigned int i = 0 ; i < multipart->parts()->count() ; i ++) {
                AbstractPart * subpart = (AbstractPart *) multipart->parts()->objectAtIndex(i);
                if (rootCid != NULL && rootCid->isEqual(subpart->contentID())) {
                    rootIndex = i;
                }
            }
            for(unsigned int i = 0 ; i < multipart->parts()->count() ; i ++) {
                AbstractPart * subpart = (AbstractPart *) multipart->parts()->objectAtIndex(i);
                if (i == rootIndex) {
                    parsePart(subpart, htmlParts, plainParts, attachments, inlineAttachments, multipart->charset());
                } else if (canPreviewPart(subpart) && subpart->contentID() != NULL && subpart->contentID() != MCSTR("")) {
                    // This is the ONLY case that DONOT call recursion
                    if (inlineAttachments != NULL) {
                        inlineAttachments->addObject(subpart);
                        subpart->setInlineAttachment(true);
                    }
                } else {
                    parsePart(subpart, htmlParts, plainParts, attachments, inlineAttachments, multipart->charset());
                }
            }
        }
        case PartTypeMultipartAlternative:{
            AbstractPart * preferedHTML = NULL;
            AbstractPart * preferedPlain = NULL;
            AbstractPart * preferedCalendar = NULL;
            AbstractMultipart * multipart = (AbstractMultipart *)part;
            unsigned int partCount = multipart->parts()->count();
            if (partCount <= 0) {
                break;
            }
            for(unsigned int i = 0 ; i < partCount ; i ++) {
                AbstractPart * subpart = (AbstractPart *) multipart->parts()->objectAtIndex(i);
                if (partContainsMimeType(subpart, MCSTR("text/html"))) {
                    preferedHTML = subpart;
                }
                else if (partContainsMimeType(subpart, MCSTR("text/plain"))) {
                    preferedPlain = subpart;
                }
                else if (partContainsMimeType(subpart, MCSTR("text/calendar"))){
                    preferedCalendar = subpart;
                }
            }
            if (preferedHTML == NULL) {
                if (preferedPlain) {
                    preferedHTML = preferedPlain;
                }
                else if (preferedCalendar) {
                    preferedHTML = preferedCalendar;
                }
                else {
                   preferedHTML = (AbstractPart *) multipart->parts()->objectAtIndex(0);
                }
            }
            if (preferedPlain == NULL) {
                if (preferedHTML) {
                    preferedPlain = preferedHTML;
                }
                else if (preferedCalendar) {
                    preferedPlain = preferedCalendar;
                }
                else {
                   preferedPlain = (AbstractPart *) multipart->parts()->objectAtIndex(0);
                }
            }
            if (preferedHTML) {
                parsePart(preferedHTML, htmlParts, NULL, attachments, inlineAttachments,  multipart->charset());
            }
            if (preferedPlain) {
                parsePart(preferedPlain, NULL, plainParts, attachments, inlineAttachments, multipart->charset());
            }
            //If there is a calendar part in alternative, we will also choose it with html part
            if (preferedCalendar && preferedCalendar != preferedHTML) {
                parsePart(preferedCalendar, htmlParts, NULL, NULL, NULL, multipart->charset());
            }
            break;
        }
        case PartTypeMultipartMixed:
        case PartTypeMultipartSigned:
        default: {
            AbstractMultipart * multipart = (AbstractMultipart *)part;
            String * mimeType = multipart->mimeType();
            // RFC: https://tools.ietf.org/html/rfc6522
            // the Reporting of Mail System Administrative Messages
            if (MCSTR("multipart/REPORT")->isEqualCaseInsensitive(mimeType)) {
                for(unsigned int i = 0 ; i < multipart->parts()->count() ; i ++) {
                    AbstractPart * subpart = (AbstractPart *) multipart->parts()->objectAtIndex(i);
                    if(MCSTR("message/delivery-status")->isEqualCaseInsensitive(subpart->mimeType())) {
                        // Skip the part for machine
                        continue;
                    }
                    parsePart(subpart, htmlParts, plainParts, attachments, inlineAttachments, multipart->charset());
                }
            }
            else {
                for(unsigned int i = 0 ; i < multipart->parts()->count() ; i ++) {
                    AbstractPart * subpart = (AbstractPart *) multipart->parts()->objectAtIndex(i);
                    parsePart(subpart, htmlParts, plainParts, attachments, inlineAttachments, multipart->charset());
                }
            }
        }
    }
}
void IMAPPartParser::parseMessage(AbstractMessage * message, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments){
    AbstractPart * mainPart = NULL;
    
    if (message->className()->isEqual(MCSTR("mailcore::IMAPMessage"))) {
        mainPart = ((IMAPMessage *) message)->mainPart();
    }
    else if (message->className()->isEqual(MCSTR("mailcore::MessageParser"))) {
        mainPart = ((MessageParser *) message)->mainPart();
    }
    if (mainPart == NULL) {
        // needs a mainPart.
        MCAssert(mainPart != NULL);
        return;
    }
    parsePart(mainPart, htmlParts, plainParts, attachments, inlineAttachments, mainPart->charset());
}
