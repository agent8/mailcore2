//
//  testString.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/17.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "ediunittest.h"
#include <sstream>

using namespace mailcore;

class testMailcoreString : public testing::Test {
protected:
    virtual void SetUp() override {

    }
    virtual void TearDown() override {
        
    }
    std::string testStr = "THIS IS A TEST String!";
    int mlength = 22;
};

TEST_F(testMailcoreString, stringDefaultFunc) {
    String * messageID = new String();
    messageID->appendString(String::uuidString());
    testStr = messageID->UTF8Characters();
    messageID->appendUTF8Characters("@");
    testStr.append("@");
    messageID->appendString(MCSTR("edison.tech"));
    testStr.append("edison.tech");
    EXPECT_STREQ(testStr.c_str(), messageID->UTF8Characters());
    messageID->release();
}

TEST_F(testMailcoreString, string_) {
    String * result = String::string();
    result->appendString(MCSTR("testString"));
    result->appendUTF8Format(":%d ", 10);
    EXPECT_STREQ("testString:10 ", result->UTF8Characters());
    result->release();
}

TEST_F(testMailcoreString, stringWithData) {
    Data * retData = new Data(testStr.c_str(), testStr.length());
    (Data *) retData->autorelease();
    mailcore::String * dataStr = mailcore::String::stringWithData(retData, "UTF-8");
    EXPECT_STREQ(testStr.c_str(), dataStr->UTF8Characters());
    dataStr->release();
}

TEST_F(testMailcoreString, stringWithUTF8Format) {
    mailcore::String * dataStr = String::stringWithUTF8Format("<%s: %i bytes>", testStr.c_str(), testStr.length());
    std::ostringstream stream;
    stream << "<" << testStr << ": " << mlength << " bytes>";
    
    EXPECT_STREQ(stream.str().c_str(), dataStr->UTF8Characters());
    dataStr->release();
}

TEST_F(testMailcoreString, stringWithUTF8Characters) {
    mailcore::String * dataStr = String::stringWithUTF8Characters(testStr.c_str());
    EXPECT_STREQ(testStr.c_str(), dataStr->UTF8Characters());
    dataStr->release();
}

TEST_F(testMailcoreString, stringWithCharacters) {
    mailcore::String * dataStr = String::stringWithUTF8Characters(testStr.c_str());
    const UChar * ucharstr = dataStr->unicodeCharacters();
    String * subStr = String::stringWithCharacters(ucharstr, 10);
    
    std::string result = "THIS IS A ";
    EXPECT_STREQ(result.c_str(), subStr->UTF8Characters());
    dataStr->release();
}

TEST_F(testMailcoreString, setString) {
    mailcore::String * dataStr = String::stringWithUTF8Characters("first string");
    EXPECT_STREQ("first string", dataStr->UTF8Characters());
    dataStr->setUTF8Characters(testStr.c_str());
    EXPECT_STREQ(testStr.c_str(), dataStr->UTF8Characters());
    dataStr->release();
}

TEST_F(testMailcoreString, stringByDecodingMIMEHeaderValue2) {
    const char * phrase3 = "=?gb2312?B?TWljcm9zb2Z0IE91dGxvb2sgyNXA+g==?=";
    mailcore::String * charsetHint = mailcore::String::stringWithUTF8Characters("utf-8");
    mailcore::String * dataStr =  mailcore::String::stringByDecodingMIMEHeaderValue2(phrase3, charsetHint);
    EXPECT_STREQ("Microsoft Outlook 日历", dataStr->UTF8Characters());
    dataStr->release();
}

TEST_F(testMailcoreString, stringByDecodingMIMEHeaderValue) {
    const char * phrase3 = "=?gb2312?B?TWljcm9zb2Z0IE91dGxvb2sgyNXA+g==?=";
    mailcore::String * dataStr =  mailcore::String::stringByDecodingMIMEHeaderValue(phrase3);
    EXPECT_STREQ("Microsoft Outlook 日历", dataStr->UTF8Characters());
    dataStr->release();
}

TEST_F(testMailcoreString, stringByDecodingMIMEHeaderValueRfc2231) {
    mailcore::String * mstr =  mailcore::String::stringByDecodingMIMEHeaderValueRfc2231("utf-8'7bit'10%E5%B9%B4%E8%BD%AF%E4%BB%B6%E6%B5%8B%E8%AF%95%E5%B7%A5%E4%BD%9C%E6%80%BB%E7%BB%93.docx");
    EXPECT_STREQ(mstr->UTF8Characters(), "10年软件测试工作总结.docx");
}

TEST_F(testMailcoreString, replaceOccurrencesOfString) {
    mailcore::String * dataStr = String::stringWithUTF8Characters(testStr.c_str());
    dataStr->replaceOccurrencesOfString(MCSTR(" A "), MCSTR(" a "));
    EXPECT_STREQ("THIS IS a TEST String!", dataStr->UTF8Characters());
}

TEST_F(testMailcoreString, testUtf7Decode) {
    const char * input = "<mailto:googlegroups-manage+267564903559+unsubscribe@googlegroups.com>, <https://groups.google.com/a/americancng.com/group/office/subscribe>";
    mailcore::String * defaultCharset1 = mailcore::String::stringWithUTF8Characters("utf-7");
    String *s1 = String::stringByDecodingMIMEHeaderValue2(input, defaultCharset1);
    // use utf-7 to decode '+' will generate error codes
    EXPECT_STRNE(input, s1->UTF8Characters());
    //std::cout << "mailcore::String:" << s1->UTF8Characters() << std::endl;

    mailcore::String * defaultCharset2 = mailcore::String::stringWithUTF8Characters("utf-8");
    String *s2 = String::stringByDecodingMIMEHeaderValue2(input, defaultCharset2);
    EXPECT_STREQ(input, s2->UTF8Characters());
}
