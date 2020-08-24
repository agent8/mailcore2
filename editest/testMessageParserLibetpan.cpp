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

void libetpanParseMessageFromLocalPath(const std::string & filename)
{
    mailcore::IMAPSession * session;
    mailimap * mImap;
    struct mailimap_response * fetch_result = nullptr;
    
    session = new mailcore::IMAPSession();
    mailcore::IMAPMessagesRequestKind requestKind = mailcore::IMAPMessagesRequestKindFullHeaders;
    //session->testSetMsgAttHandler(requestKind);
    
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
                mailcore::IMAPMessage* message =  (mailcore::IMAPMessage*)messages->objectAtIndex(i);
               // std::cout << "***********************************************************************" <<  std::endl;
               // std::cout << "UID       :" << message->uid() <<  std::endl;
                mailcore::MessageHeader * header = message->header();
                if (header) {
                    mailcore::String * subject = header->subject();
                    if (subject) {
                       // std::cout << "Subject   :" << subject->UTF8Characters() <<  std::endl;
                    }
                    mailcore::String * messageID = header->messageID();
                    if (messageID) {
                        //std::cout << "Message-ID:" << messageID->UTF8Characters() <<  std::endl;
                    }
                }
                //std::cout << "size      :" << message->size() <<  std::endl;
                //std::cout << "flags     :" << message->flags() <<  std::endl;

                mailcore::AbstractPart*  parts = message->mainPart();
                if (parts) {
                    //std::cout << "MainPart  :" << parts->description()->UTF8Characters() <<  std::endl;
                }
                mailcore::Data * partData = message->partData();
                if (partData) {
                    //std::cout << "PartData  :" << partData->description()->UTF8Characters() <<  std::endl;
                }
            }
            //std::cout << "***********************************************************************" <<  std::endl;
        }
    }
}

TEST(testMessageParserLibetpan, libetpanParseMessageFromLocalPath) {
    const std::string filename = "editest/data/parser/headerstream/msg_header_qq_resp.txt";
    
    libetpanParseMessageFromLocalPath(filename);
}
