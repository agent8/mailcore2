//
//  testMessageParserLibetpan.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/20.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "ediunittest.h"
#include <libetpan/libetpan.h>
#include <libetpan/mailimap.h>
#include "EditestFileUtils.hpp"
#include "EdiTestCheckResult.hpp"

static void editest_body_progress(size_t current, size_t maximum, void * context)
{
    mailcore::IMAPSession * session = (mailcore::IMAPSession *) context;
    
    //std::cout << "BodyProgress :" << current << "/" << maximum <<  std::endl;
}

static void editest_items_progress(size_t current, size_t maximum, void * context)
{
    mailcore::IMAPSession * session = (mailcore::IMAPSession *) context;
    
    //std::cout << "ItemsProgress:" << current << "/" << maximum << std::endl;
}
static void editest_logger(mailimap * imap, int log_type, const char * buffer, size_t size, void * context)
{
    mailcore::IMAPSession * session = (mailcore::IMAPSession *) context;
}

std::vector<EdiTestCheckResult> libetpanParseMessageFromLocalFile(const std::string & filename)
{
    std::vector<EdiTestCheckResult> resultList;
    mailcore::IMAPSession * session;
    mailimap * mImap;
    struct mailimap_response * fetch_result = nullptr;
    
    session = new mailcore::IMAPSession();
    mailcore::IMAPMessagesRequestKind requestKind = mailcore::IMAPMessagesRequestKindFullHeaders;
    
    mImap = mailimap_new(0, NULL);
    mImap->imap_tag = 7; //Corresponding to "7 OK FETCH Completed"
    
    mailimap_set_timeout(mImap, 30);
    mailimap_set_progress_callback(mImap, editest_body_progress, editest_items_progress, session);
    mailimap_set_logger(mImap, editest_logger, session);
    mailcore::IMAPSession::testSetMsgAttHandler(mImap, requestKind);
    
    std::string input = EditestFileUtils::getStringFromLocalFile(filename.c_str());
    
    mImap->imap_stream_buffer = mmap_string_new(input.c_str());
    
    mImap->imap_response_buffer = mmap_string_new("");
    
    int parseResult = mailimap_parse_response(mImap, &fetch_result);
    if (parseResult == MAILIMAP_NO_ERROR) {
        mailcore::Array * messages = mailcore::IMAPSession::testGetParsedMessage(mImap);
        if (messages) {
            for (int i = 0; i  < messages->count(); i++) {
                EdiTestCheckResult result;
                mailcore::IMAPMessage* message =  (mailcore::IMAPMessage*)messages->objectAtIndex(i);
                result.uid = message->uid();
                mailcore::MessageHeader * header = message->header();
                if (header) {
                    mailcore::String * subject = header->subject();
                    if (subject) {
                       result.subject = subject->UTF8Characters();
                    }
                    mailcore::String * messageID = header->messageID();
                    if (messageID) {
                        //std::cout << "Message-ID:" << messageID->UTF8Characters() <<  std::endl;
                    }
                    mailcore::Address * from = header->from();
                     if (from) {
                         result.from = from->mailbox()->UTF8Characters();
                     }

                     mailcore::Array * to = header->to();
                     if (to) {
                         result.toCount = to->count();
                     }

                     mailcore::Array * cc = header->cc();
                     if (cc) {
                         result.ccCount = cc->count();
                     }

                     mailcore::Array * bcc = header->bcc();
                     if (bcc) {
                         result.bccCount = bcc->count();
                     }
                }
                result.size = message->size();
                //std::cout << "flags     :" << message->flags() <<  std::endl;

                mailcore::AbstractPart*  parts = message->mainPart();
                if (parts) {
                    //std::cout << "MainPart  :" << parts->description()->UTF8Characters() <<  std::endl;
                    mailcore::Array * htmlParts = mailcore::Array::array();
                    mailcore::Array * plainParts = mailcore::Array::array();
                    mailcore::Array * attachmentParts = mailcore::Array::array();
                    mailcore::Array * inlineAttachmentParts = mailcore::Array::array();
                    mailcore::IMAPPartParser::parseMessage(message, htmlParts, plainParts, attachmentParts, inlineAttachmentParts);
                    result.htmlParts = htmlParts->count();
                    result.plainParts = plainParts->count();
                    result.attachmentParts = attachmentParts->count();
                    result.inlineAttachmentParts = inlineAttachmentParts->count();
                }
                mailcore::Data * partData = message->partData();
                if (partData) {
                    //std::cout << "PartData  :" << partData->description()->UTF8Characters() <<  std::endl;
                }
                resultList.emplace_back(result);
            }
        }
    }
    return resultList;
}

void testImapDataFromLocalFile(const std::string & filepath) {
    std::vector<EdiTestCheckResult> fileResults = libetpanParseMessageFromLocalFile(filepath);
    std::string filename = EditestFileUtils::getFileNameFromPath(filepath);
    
    std::map<uint32_t, EdiTestCheckResult> expectedResults = EdiTestCheckResult::parseImapHeaderResult("editest/data/parser/headerstream/expect-stream-results.csv", filename);
    
    EXPECT_EQ(fileResults.size(), expectedResults.size());
    
    for (auto & fr : fileResults) {
        std::map<uint32_t, EdiTestCheckResult>::iterator it = expectedResults.find(fr.uid);
        
        if (it == expectedResults.end()) {
            EXPECT_FALSE(true) << "file expectResult does not exist:" << fr.uid;
        } else {
            EdiTestCheckResult::checkImapHeaderResult(fr, it->second);
        }
    }
    
}


TEST(testMessageParserLibetpan, testImapDataFromLocalFile) {
    std::string filepath = "editest/data/parser/headerstream/msg_header_qq_resp.txt";
    testImapDataFromLocalFile(filepath);
}

TEST(testMessageParserLibetpan, testImapDataFromLocalPath) {
    const std::string root = "editest/data/parser/headerstream/";
    std::vector<std::string> files = EdiTestCheckResult::getAllFiles(root, "txt");
    for (auto & filename : files) {
        std::string filepath = root + filename;
        testImapDataFromLocalFile(filepath);
    }
}
