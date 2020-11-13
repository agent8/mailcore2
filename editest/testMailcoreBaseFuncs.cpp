//
//  testMailcoreBaseFuncs.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/11.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "ediunittest.h"

static std::string testStringByDecodingMIMEHeaderValue2(const char * phrase, const char * charset) {
    mailcore::String * charsetHint = mailcore::String::stringWithUTF8Characters(charset);
    
    mailcore::String * mstr =  mailcore::String::stringByDecodingMIMEHeaderValue2(phrase, charsetHint);
    std::string result = mstr->UTF8Characters();
    return result;
}

static std::string testStringByDecodingMIMEHeaderValueRfc2231(const char * phrase) {
    std::string result;
    mailcore::String * mstr =  mailcore::String::stringByDecodingMIMEHeaderValueRfc2231(phrase);
    if (mstr) {
        result = mstr->UTF8Characters();
    } else {
        //std::cout << "Result: decode failed for " << phrase << std::endl;
    }
    return result;
}

TEST(testMailcoreBaseFuncs, DecodingMIMEHeaderValue2) {
    
    const char * phrase = "\r\n =?utf-8?Q?=E6=94=B9=E5=8F=98=E4=BA=86role=E5=92=8C=E6=96=87=E4=BB=B6=E5=A4=B9=E7=9A=84=E6=B5=8B=E8=AF=95?=";
    std::string result = testStringByDecodingMIMEHeaderValue2(phrase, "utf-8");
    EXPECT_STREQ(result.c_str(), "改变了role和文件夹的测试");
    
    const char * phrase2 = "=?GBK?B?uPy6w7XEzsq68g==?=";
    result = testStringByDecodingMIMEHeaderValue2(phrase2, "utf-8");
    EXPECT_STREQ(result.c_str(), "更好的问候");
    
    const char * phrase3 = "=?gb2312?B?TWljcm9zb2Z0IE91dGxvb2sgyNXA+g==?=";
    result = testStringByDecodingMIMEHeaderValue2(phrase3, "utf-8");
    EXPECT_STREQ(result.c_str(), "Microsoft Outlook 日历");
    
    const char * phrase4 = "=?gb2312?B?MjAxN8TqMTLUwjfI1SC1xMO/yNW8xruu?=";
    result = testStringByDecodingMIMEHeaderValue2(phrase4, "utf-8");
    EXPECT_STREQ(result.c_str(), "2017年12月7日 的每日计划");
    
    const char * phrase5 = "This string has no encoding.";
    result = testStringByDecodingMIMEHeaderValue2(phrase5, "utf-8");
    EXPECT_STREQ(result.c_str(), "This string has no encoding.");
}

TEST(testMailcoreBaseFuncs, DecodingMIMEHeaderValueRfc2231) {
    std::string result;
    result = testStringByDecodingMIMEHeaderValueRfc2231("utf-8'7bit'10%E5%B9%B4%E8%BD%AF%E4%BB%B6%E6%B5%8B%E8%AF%95%E5%B7%A5%E4%BD%9C%E6%80%BB%E7%BB%93.docx");
    EXPECT_STREQ(result.c_str(), "10年软件测试工作总结.docx");
    
    result = testStringByDecodingMIMEHeaderValueRfc2231("utf-8'base64'10%E5%B9%B4%E8%BD%AF%E4%BB%B6%E6%B5%8B%E8%AF%95%E5%B7%A5%E4%BD%9C%E6%80%BB%E7%BB%93.docx");
    EXPECT_STREQ(result.c_str(), "10年软件测试工作总结.docx");
    
    result = testStringByDecodingMIMEHeaderValueRfc2231("gb2312''IMClient%CA%FD%BE%DD%C2%DF%BC%AD%B2%E3%CC%D6%C2%DB%B8%E5.eml");
    EXPECT_STREQ(result.c_str(), "IMClient数据逻辑层讨论稿.eml");
    
    result = testStringByDecodingMIMEHeaderValueRfc2231("gb2312''IMClient%CA%FD%BE%DD%C2%DF%BC%AD%B2%E3%CC%D6%C2%DB%B8%E5.pptx");
    EXPECT_STREQ(result.c_str(), "IMClient数据逻辑层讨论稿.pptx");
    
    result = testStringByDecodingMIMEHeaderValueRfc2231("GB2312''%CA%D3%C6%B5.MOV");
    EXPECT_STREQ(result.c_str(), "视频.MOV");
    
    result = testStringByDecodingMIMEHeaderValueRfc2231("abc");
    EXPECT_STREQ(result.c_str(), "");
    
    result = testStringByDecodingMIMEHeaderValueRfc2231("gb2312''%D4%AD%CE%C4.txt");
    EXPECT_STREQ(result.c_str(), "原文.txt");
}
