//
//  testMessageParser.h
//  editest
//
//  Created by 徐雷 on 2020/8/11.
//  Copyright © 2020 MailCore. All rights reserved.
//

#ifndef testMessageParser_h
#define testMessageParser_h

#include <MailCore/MailCore.h>
#include "testEdiMessage.h"
#include "EdiTestCheckResult.hpp"

class testMessageParser {
public:
    static void parseMessageHeader(mailcore::MessageHeader* header, testEdiMessage * message);
    static testEdiMessage * parseIMAPMessage(mailcore::IMAPMessage * imapMessage);
    static void parseMessageFromFile(mailcore::String * input, mailcore::String * output);
    static testEdiMessage * parserMessageParserToEdiMessage(mailcore::MessageParser * parser);
    static void parseMessageFromLocalPath(mailcore::String * inputPath);
    static EdiTestCheckResult parseMessageFromLocalFile(mailcore::String * inputPath);
    static void parseIMAPMessageFromServer(mailcore::IMAPMessage * imapMessage);
    static void WriteDataToFile(mailcore::Data * data, const std::string & filename);
    static void parseEmlHtmlBodyToFile(mailcore::String * filename);
};

#endif /* testMessageParser_h */
