//
//  testMessageHeader.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/6.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "ediunittest.h"


void testMailcoreMessageHeader() {
    mailcore::MessageHeader* header = new mailcore::MessageHeader();
    mailcore::String * hkeyListId = mailcore::String::uniquedStringWithUTF8Characters("List-ID");
    mailcore::String * listId = header->extraHeaderValueForName(hkeyListId);
    const std::string ltId = "List-ID--000000011111";
    const std::string recvStr = "this is a test Received,";
    if (listId) {
        const char * listIdStr = listId->UTF8Characters();
        std::cout << listIdStr << std::endl;
    } else {
        header->setExtraHeader(hkeyListId, mailcore::String::uniquedStringWithUTF8Characters("List-ID--000000011111"));
        header->setExtraHeader(hkeyListId, mailcore::String::uniquedStringWithUTF8Characters(ltId.c_str()));
    }

    char * fieldValue = new char[100];
    mailcore::String * fieldValueStr;
    mailcore::String * fieldNameStr;
    
    fieldNameStr = mailcore::String::uniquedStringWithUTF8Characters("Received");
    for (int i = 0; i < 3; i++) {
        sprintf(fieldValue, "%s%d", recvStr.c_str(), i);
        fieldValueStr = mailcore::String::uniquedStringWithUTF8Characters(fieldValue);
        if (fieldValueStr != NULL) {
            header->setExtraHeader(fieldNameStr, fieldValueStr);
        }
    }
    mailcore::String * sigleRecv = header->extraHeaderValueForName(fieldNameStr);
    mailcore::Array * arrRecv = header->extraHeaderValuesForName(fieldNameStr);
    const char * sigStr = sigleRecv->UTF8Characters();
    EXPECT_STREQ(sigStr, "this is a test Received,0");
    for (int i = 0; i < arrRecv->count(); i++) {
        auto mstr = (mailcore::String * )arrRecv->objectAtIndex(i);
        std::string str = mstr->UTF8Characters();
        EXPECT_STREQ(str.c_str(), (recvStr+std::to_string(i)).c_str());
    }
    
    mailcore::String * list1 = header->extraHeaderValueForName(hkeyListId);
    mailcore::Array * list2 = header->extraHeaderValuesForName(hkeyListId);
    std::string siglist1 = list1->UTF8Characters();
    EXPECT_STREQ(siglist1.c_str(), ltId.c_str());
    for (int i = 0; i < list2->count(); i++) {
        auto mstr = (mailcore::String * )list2->objectAtIndex(i);
        std::string str = mstr->UTF8Characters();
        EXPECT_STREQ(str.c_str(), ltId.c_str());
    }
    
    delete [] fieldValue;
}

void testMailcoreMessageHeaderDescription() {
    mailcore::MessageHeader* header = new mailcore::MessageHeader();
    mailcore::String * keyListId = MCSTR("List-ID");
    mailcore::String * valueListId = MCSTR("Vaule of listID");
    header->setExtraHeader(keyListId, valueListId);
    
    mailcore::String * testStr = MCSTR("TESTSTR");
    mailcore::String * testValue = MCSTR("TESTVALUE");
    header->setExtraHeader(testStr, testValue);

    mailcore::String * fieldNameStr = MCSTR("Received");
    header->setExtraHeader(fieldNameStr, MCSTR("value r1"));
    header->setExtraHeader(fieldNameStr, MCSTR("value r2"));
    header->setExtraHeader(fieldNameStr, MCSTR("value r3"));
    
    mailcore::String * result = header->description();
    std::cout << result->UTF8Characters() << std::endl;

    mailcore::String * testValueResult = header->extraHeaderValueForName(testStr);
    EXPECT_STREQ(testValueResult->UTF8Characters(), "TESTVALUE");
    
    mailimf_fields * f = header->createIMFFieldsAndFilterBcc(false);
    
}

TEST(testMessageHeader, test0)
{
    testMailcoreMessageHeader();
}

TEST(testMessageHeader, description)
{
    testMailcoreMessageHeaderDescription();
}
