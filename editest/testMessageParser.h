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

class testMessageParser {
public:
    static void parseMessageHeader(mailcore::MessageHeader* header, testEdiMessage * message);
    static testEdiMessage * parseIMAPMessage(mailcore::IMAPMessage * imapMessage);
};

#endif /* testMessageParser_h */