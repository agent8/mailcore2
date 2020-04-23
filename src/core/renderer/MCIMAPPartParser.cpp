//
//  MCIMAPPartParser.cpp
//  mailcore2
//
//  Created by weicheng qian on 2019/11/27.
//  Copyright © 2019 MailCore. All rights reserved.
//

#include "MCIMAPPartParser.h"

using namespace mailcore;
#ifdef ENABLE_INLINE_ALL_IMAGE
bool ALL_IMAGE_AS_INLINE = true;
#else
bool ALL_IMAGE_AS_INLINE = false;
#endif
static bool partContainsMimeType(AbstractPart * part, String * mimeType);

static bool isTextPart(AbstractPart * part)
{
    String * mimeType = part->mimeType();
    if (part->filename() != NULL && !MCSTR("")->isEqual(part->filename())) {
        // Do not inline text part
        return false;
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

static bool isImagePart(AbstractPart * part) {
    String * mimeType = part->mimeType();
    String * filename = part->filename();
    // is mimetype start with image/ or filename endwith .jpg/.jpeg/.png/.gif, .etc.
    if (mimeType != NULL) {
        if (mimeType->lowercaseString()->hasPrefix(MCSTR("image/"))) {
            return true;
        }
    }
    if (filename != NULL) {
        String * ext = filename->pathExtension();
        if (MCSTR("jpg")->isEqualCaseInsensitive(ext) ||
            MCSTR("jpeg")->isEqualCaseInsensitive(ext) ||
            MCSTR("png")->isEqualCaseInsensitive(ext) ||
            MCSTR("gif")->isEqualCaseInsensitive(ext) ||
            MCSTR("bmp")->isEqualCaseInsensitive(ext)) {
            // ICO,SVG,TIFF,APNG,WebP
            // https://en.wikipedia.org/wiki/Comparison_of_web_browsers#Image_format_support
            // We need to support two web browsers: chrome(Desktop,Android) & Safari(iOS).
            // I only add the image formats that supported both of the two browsers.
            // We can add more formats if need to support special platform only.
            return true;
        }
    }
    return false;
}
static bool isInlinePart(AbstractPart * part, bool strict) {
    if (strict) {
        // In single part
        if (ALL_IMAGE_AS_INLINE || !part->isAttachment()) {
           return isImagePart(part);
        }
    }
    else {
        // In multipart/related
        if (part->contentID() != NULL && !MCSTR("")->isEqual(part->contentID())) {
            return isImagePart(part);
        }
    }
    return false;
}

static bool partContainsMimeType(AbstractPart * part, String * mimeType)
{
    MCAssert(part != NULL);
    if (part->mimeType() != NULL && part->mimeType()->isEqualCaseInsensitive(mimeType)) {
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

static void prettyPrintPart(String * output, AbstractPart * part,Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments, int level) {
    for (int i=0; i<level; i++){
        output->appendString(MCSTR("    "));
    }
    String * mimetype = part->mimeType();
    switch (part->partType()) {
        case PartTypeSingle:
        case PartTypeMessage: {
            String * tags = String::string();
            if (htmlParts && htmlParts->containsObject(part)) {
                tags->appendString(MCSTR(" html"));
            }
            if (plainParts && plainParts->containsObject(part)) {
                tags->appendString(MCSTR(" plain"));
            }
            if (attachments && attachments->containsObject(part)) {
                // part->isAttachment()
                tags->appendString(MCSTR(" attachment"));
            }
            if (inlineAttachments && inlineAttachments->containsObject(part)) {
                // part->isInlineAttachment()
                tags->appendString(MCSTR(" inline"));
            }
            if (mimetype == NULL) {
                mimetype = MCSTR("application/x-unknown-edison");
            }
            output->appendString(String::stringWithUTF8Format("%s %s >%s\r\n", part->partID()->UTF8Characters(), mimetype->UTF8Characters(), tags->UTF8Characters()));
            break;
        }
        default: {
            if (mimetype == NULL) {
                if (part->partType() == PartTypeMultipartMixed) {
                    mimetype = MCSTR("multipart/mixed");
                }
                else if (part->partType() == PartTypeMultipartSigned) {
                    mimetype = MCSTR("multipart/signed");
                }
                else if (part->partType() == PartTypeMultipartRelated) {
                    mimetype = MCSTR("multipart/related");
                }
                else if (part->partType() == PartTypeMultipartAlternative) {
                    mimetype = MCSTR("multipart/alternative");
                }
                else {
                    mimetype = MCSTR("multipart/x-edison-unknown");
                }
            }
            if (part->partID() == NULL || MCSTR("")->isEqual(part->partID())) {
                output->appendString(String::stringWithUTF8Format("%s(root)\r\n", mimetype->UTF8Characters()));
            }
            else {
                output->appendString(String::stringWithUTF8Format("%s %s\r\n", part->partID()->UTF8Characters(), mimetype->UTF8Characters()));
            }
            AbstractMultipart * multipart = (AbstractMultipart *)part;
            for(unsigned int i = 0 ; i < multipart->parts()->count() ; i ++) {
                AbstractPart * subpart = (AbstractPart *) multipart->parts()->objectAtIndex(i);
                prettyPrintPart(output, subpart, htmlParts, plainParts, attachments, inlineAttachments, level+1);
            }
            break;
        }
    }
}

void IMAPPartParser::parsePart(AbstractPart * part, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments, String * defaultCharset){
    // https://tools.ietf.org/html/rfc2046
    // Note: Fill the fields(charset and mimetype). We DO NOT trust inline and attachment field from RFC822.
    String * charset = part->charset();
    if ((charset == NULL || MCSTR("")->isEqual(charset)) && defaultCharset != NULL) {
        part->setCharset(defaultCharset);
    }
    switch (part->partType()) {
        case PartTypeSingle: {
            if (part->mimeType() == NULL) {
                part->setMimeType(MCSTR("application/octet-stream"));
            }
            if (isTextPart(part)) {
                if (htmlParts != NULL) {
                    htmlParts->addObject(part);
                }
                if (plainParts != NULL) {
                    plainParts->addObject(part);
                }
            } else if (isInlinePart(part, true)) {
                // We prefer to display an image into html body instead of attachments.
                if (part->contentID() == NULL || MCSTR("")->isEqual(part->contentID())) {
                    if (htmlParts != NULL) {
                        htmlParts->addObject(part);
                    }
                    if (inlineAttachments != NULL) {
                        inlineAttachments->addObject(part);
                        part->setInlineAttachment(true);
                    }
                }
                else {
                    if (part->isInlineAttachment()) {
                        // Normal inline images
                        if (inlineAttachments != NULL) {
                            inlineAttachments->addObject(part);
                            part->setInlineAttachment(true);
                        }
                    }
                    else {
                        // This is ONLY for the email that do not follow the RFC2387.
                        // Add into attachments instead of inline for safety
                        if (attachments != NULL) {
                            attachments->addObject(part);
                            part->setAttachment(true);
                        }
                    }
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
                } else if (isInlinePart(subpart, false)) {
                    if (inlineAttachments != NULL) {
                        inlineAttachments->addObject(subpart);
                        subpart->setInlineAttachment(true);
                    }
                } else {
                    parsePart(subpart, htmlParts, plainParts, attachments, inlineAttachments, multipart->charset());
                }
            }
            break;
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
            if (!preferedHTML && preferedPlain) {
                preferedHTML = preferedPlain;
            }
            if (!preferedPlain && preferedHTML) {
                preferedPlain = preferedHTML;
            }
            //Note: preferedHTML&preferedPlain should be 1,1 or 0,0; never be 0,1 or 1,0
            if (preferedHTML && preferedPlain) {
                parsePart(preferedHTML, htmlParts, NULL, attachments, inlineAttachments,  multipart->charset());
                parsePart(preferedPlain, NULL, plainParts, attachments, inlineAttachments, multipart->charset());
            }
            //If there is a calendar part in alternative, we will also choose it with html part
            if (preferedCalendar) {
                if (htmlParts) {
                    htmlParts->addObject(preferedCalendar);
                }
                if (inlineAttachments) {
                    inlineAttachments->addObject(preferedCalendar);
                }
            }
            
            break;
        }
        case PartTypeMultipartMixed:
        case PartTypeMultipartSigned:
        default: {
            if (!MCSTR("mailcore::Multipart")->isEqual(part->className()) &&
                !MCSTR("mailcore::IMAPMultipart")->isEqual(part->className())) {
                //printf("Should never get here. Not supported class:%s\n",part->className()->UTF8Characters());
                MCAssert(false);
                break;
            }
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
                unsigned int partLength = multipart->parts()->count();
                for(unsigned int i = 0 ; i < partLength ; i ++) {
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

AbstractMessage * IMAPPartParser::parseMessage(String * filepath, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments) {
    mailcore::MessageParser * parser = mailcore::MessageParser::messageParserWithContentsOfFile(filepath);
    parseMessage(parser, htmlParts, plainParts, attachments, inlineAttachments);
    return parser;
}

void IMAPPartParser::fixFilename(AbstractPart * part) {
    if (part->filename() == NULL || MCSTR("")->isEqual(part->filename())) {
        String * mimetype = part->mimeType();
        if (mimetype) {
            String * ext = NULL;
            if (mimetype->hasPrefix(MCSTR("text/"))) {
                if (MCSTR("text/html")->isEqualCaseInsensitive(mimetype)) {
                    ext = MCSTR("html");
                }
                else if (MCSTR("text/calendar")->isEqualCaseInsensitive(mimetype)) {
                    ext = MCSTR("ics");
                }
                else {
                    ext = MCSTR("txt");
                }
            }
            else if (part->partType() == PartTypeMessage) {
                ext = MCSTR("eml");
            }
            else {
                ext = mimetype->lastPathComponent();
            }
            String * filename = String::stringWithUTF8Format("attachment.%s", ext->UTF8Characters());
            part->setFilename(filename);
        }
        else {
            part->setFilename(MCSTR("attachment.dat"));
        }
    } else {
        String * filename = part->filename()->filenameFix();
        part->setFilename(filename);
    }
}

String * IMAPPartParser::prettyPrint(AbstractMessage * message, Array * htmlParts, Array * plainParts, Array * attachments, Array * inlineAttachments) {
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
        return NULL;
    }
    String * output = String::string();
    prettyPrintPart(output, mainPart, htmlParts, plainParts, attachments, inlineAttachments, 0);
    return output;
}
