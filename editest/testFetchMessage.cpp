//
//  testFetchMessage.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/11.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "ediunittest.h"
#include "testMailcoreUtils.hpp"
#include "testEdiMessage.h"
#include "testEdiAccount.h"
#include "testMessageParser.h"
#include "EdiTestCheckResult.hpp"

static const std::string parserEmlPath = "editest/data/parser/eml/";

static void testFetchMessageHeadersByUid(const testEdiAccount * account, const char * fpath, uint32_t uids[], int count) {
    
    mailcore::ErrorCode errorCode = mailcore::ErrorNone;

    mailcore::IMAPSession * session = testImapSession(account);
    ASSERT_FALSE(session == NULL);
    
    mailcore::String * folderPath = mailcore::String::stringWithUTF8Characters(fpath);
    ASSERT_FALSE(folderPath == NULL);

    mailcore::IndexSet * muids = new mailcore::IndexSet();
    for (int i = 0; i < count; i++) {
        muids->addIndex(uids[i]);
    }
    //std::cout << "Message UID:" << muids->description()->UTF8Characters() << std::endl;
    
    mailcore::IMAPMessagesRequestKind requestKind = (mailcore::IMAPMessagesRequestKind)
    (mailcore::IMAPMessagesRequestKindUid | mailcore::IMAPMessagesRequestKindFlags | mailcore::IMAPMessagesRequestKindStructure |
     mailcore::IMAPMessagesRequestKindInternalDate | mailcore::IMAPMessagesRequestKindFullHeaders | mailcore::IMAPMessagesRequestKindSize | mailcore::IMAPMessagesRequestKindHeaderBcc);

    if (account->isGmail) {
        requestKind = (mailcore::IMAPMessagesRequestKind) (requestKind | mailcore::IMAPMessagesRequestKindGmailLabels | mailcore::IMAPMessagesRequestKindGmailMessageID | mailcore::IMAPMessagesRequestKindGmailThreadID);
    }
    
    mailcore::Array * messages = session->fetchMessagesByUID(folderPath, requestKind, muids, NULL, &errorCode);
    EXPECT_FALSE(messages == NULL);
    std::vector<testEdiMessage*> messageList;
    
    if (messages != NULL) {
        for (int i = 0; i  < messages->count(); i++) {
            mailcore::IMAPMessage* message =  (mailcore::IMAPMessage*)messages->objectAtIndex(i);
            testEdiMessage * edimsg = testMessageParser::parseIMAPMessage(message);
            messageList.emplace_back(edimsg);
        }
    }
    EXPECT_EQ(messages->count(), messageList.size());
//
//    for (const EdiMessage * message : messageList) {
//        test_output_message(message);
//    }

}

static void testFetchMessageContentByUidToEMLFile(const testEdiAccount * account, const char * fpath, uint32_t uids[], int count) {
    
    mailcore::ErrorCode errorCode = mailcore::ErrorNone;

    mailcore::IMAPSession * session = testImapSession(account);
    ASSERT_FALSE(session == NULL);

    mailcore::String * folderPath = mailcore::String::stringWithUTF8Characters(fpath);
    ASSERT_FALSE(folderPath == NULL);

    mailcore::IndexSet * muids = new mailcore::IndexSet();

    for (int i = 0; i < count; i++) {
        uint32_t uid = uids[i];
        mailcore::Data * data = session->fetchMessageByUID(folderPath, uid, NULL, &errorCode);
        if (data) {
            const std::string emailBasePath("editest/data/parser/eml/output/");
            std::string filepath = emailBasePath + account->email + "-" + std::to_string(uid) + ".eml";
            mailcore::String * mfp = mailcore::String::stringWithUTF8Characters(filepath.c_str());
            data->writeToFile(mfp);
        }
    }
}
static void adjustIndex(int64_t & start, int64_t & size, uint32_t totalSize) {
    int64_t fixedStart = totalSize - start - size + 1;
    int64_t fixedSize = size - 1;
    if (fixedStart < 1) {
        fixedStart = 1;
        fixedSize = totalSize - start - 1; //need to minus 1
    }
    if (fixedSize < 0) {
        fixedSize = 0;
    }

    start = fixedStart;
    size = fixedSize;
}

static void testFetchMessageHeadersByNum(const testEdiAccount * account, const char * fpath, long long start, long long size) {
    
    mailcore::ErrorCode errorCode = mailcore::ErrorNone;
    
    mailcore::IMAPSession * session = testImapSession(account);
    ASSERT_FALSE(session == NULL);
    
    mailcore::String * folderPath = mailcore::String::stringWithUTF8Characters(fpath);
    ASSERT_FALSE(folderPath == NULL);
    
    session->loginIfNeeded(&errorCode);
    ASSERT_TRUE(errorCode == mailcore::ErrorNone);
   
    session->select(folderPath, &errorCode);
    ASSERT_TRUE(errorCode == mailcore::ErrorNone);

    uint32_t total = session->lastFolderMessageCount();
    adjustIndex(start, size, total);

    mailcore::IndexSet * uids = new mailcore::IndexSet();
    mailcore::Range range;
    range.location = start;
    range.length = size;
    //std::cout << " Fetch message start. total=" << total << " start=" << start << " size=" << size << std::endl;
    
    uids->addRange(range);
    
    mailcore::IMAPMessagesRequestKind requestKind = (mailcore::IMAPMessagesRequestKind) (mailcore::IMAPMessagesRequestKindUid);
    requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindFlags);
    requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindStructure);
    requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindInternalDate);
    requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindFullHeaders);
    requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindSize);
    requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindHeaderBcc);
    
    if (account->isGmail) {
        requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindGmailLabels);
        requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindGmailMessageID);
        requestKind = (mailcore::IMAPMessagesRequestKind)(requestKind | mailcore::IMAPMessagesRequestKindGmailThreadID);
    }
    
    mailcore::Array * messages = session->fetchMessagesByNumber(folderPath, requestKind, uids, NULL, &errorCode);
    ASSERT_TRUE(messages != NULL);
    unsigned int messageCount = 0;
    if (messages) {
        messageCount = messages->count();
    }
    EXPECT_EQ(messageCount, size + 1);
    
    std::vector<testEdiMessage*> messageList;
    
    if (messages != NULL) {
        for (int i = 0; i  < messages->count(); i++) {
            mailcore::IMAPMessage* message =  (mailcore::IMAPMessage*)messages->objectAtIndex(i);
            testEdiMessage * edimsg = testMessageParser::parseIMAPMessage(message);
            messageList.emplace_back(edimsg);
        }
    }
    EXPECT_EQ(messageCount, messageList.size());
}

static void testFetchMessageContentByNumberToFile(const testEdiAccount * account, const char * fpath, uint32_t number, int count) {
    
    mailcore::ErrorCode errorCode = mailcore::ErrorNone;

    mailcore::IMAPSession * session = testImapSession(account);
    ASSERT_FALSE(session == NULL);

    mailcore::String * folderPath = mailcore::String::stringWithUTF8Characters(fpath);
    ASSERT_FALSE(folderPath == NULL);

    mailcore::IndexSet * muids = new mailcore::IndexSet();

    for (int i = 0; i < count; i++) {
        mailcore::Data * data = session->fetchMessageByNumber(folderPath, number, NULL, &errorCode);
        if (data) {
            const std::string emailBasePath("editest/data/parser/eml/output/");
            std::string filepath = emailBasePath + account->email + "-" + std::to_string(number) + ".eml";
            mailcore::String * mfp = mailcore::String::stringWithUTF8Characters(filepath.c_str());
            data->writeToFile(mfp);
        }
    }
}

TEST(testFetchMessage, fetchMessageHeaderByNum) {
    testEdiAccount * account = new testEdiAccount();
    account->email = "edotest13@gmail.com";
    account->passwd = "";
    account->accessToken = "ya29.a0AfH6SMAr1QbT6UNe8eTc20qphnAIo9eHdvSWEgJMBnhRJL-ClAXC1NfTjrWy6bGwCvOi3STm736gehOO4RS4Z5XnW_lz2Pgpe_1T7WJWsYTXT0_oiA98c1Wrz9ICqE6rgsD1XKZJjFybRLRlpKqIgFTXJJkZGD1ofvo";
    account->host = "imap.gmail.com";
    account->isGmail = true;
    std::string fpath = "INBOX";
//    testFetchMessageHeadersByNum(account, fpath.c_str(), 1, 100);
    delete account;
}

class FetchMessageHeaderTest : public testing::Test {
protected:
    virtual void SetUp() override {
        account = new testEdiAccount();
        account->email = "edotest1@126.com";
        account->passwd = "A1234567";
        account->host = "imap.126.com";
        account->isGmail = false;
    }
    virtual void TearDown() override {
        delete account;
    }
    testEdiAccount * account;
    std::string fpath = "INBOX";
};

TEST_F(FetchMessageHeaderTest, fetchMessageHeaderByUid) {
    uint32_t test_uids[] = {1433921373};
    int count = (int)sizeof(test_uids)/sizeof(test_uids[0]);
    testFetchMessageHeadersByUid(account, fpath.c_str(), test_uids, count);
}

TEST_F(FetchMessageHeaderTest, testFetchMessageHeadersByNum) {
    testFetchMessageHeadersByNum(account, fpath.c_str(), 1, 100);
}

TEST_F(FetchMessageHeaderTest, testFetchMessageContentByUidToEMLFile) {
    uint32_t test_uids[] = {1433921373, 1433921416};
    int count = (int)sizeof(test_uids)/sizeof(test_uids[0]);
//    testFetchMessageContentByUidToEMLFile(account, fpath.c_str(), test_uids, count);
}


TEST(testFetchMessage, parseMessageFromLocalPath) {
    const std::string root = parserEmlPath + "input/";
    std::vector<std::string> files = EdiTestCheckResult::getAllFiles(root, "eml");
    std::map<std::string, EdiTestCheckResult> expectedResults = EdiTestCheckResult::parseExpectedResult(parserEmlPath + "input/expect-results.csv", 1);
    int total = 0;
    int pass = 0;
    for (std::string & file : files) {
        total++;
        std::string filepath = root + file;
        mailcore::String * inputPath = mailcore::String::stringWithUTF8Characters(filepath.c_str());
        EdiTestCheckResult fileResult = testMessageParser::parseMessageFromLocalFile(inputPath);

        std::map<std::string, EdiTestCheckResult>::iterator it = expectedResults.find(file);
        
        if (it == expectedResults.end()) {
            EXPECT_FALSE(true) << "file expectResult does not exist:" << file.c_str();
        } else {
            EdiTestCheckResult::checkEmlResult(file, fileResult, it->second);
            pass++;
        }
    }
    EXPECT_EQ(pass, total);
}

TEST(testFetchMessage, parseMessageFromLocalFile) {
    std::string rootpath = parserEmlPath + "input/";
    std::string filename = "rfc2060.eml";
    std::string filepath = rootpath + filename;
    mailcore::String * inputPath = mailcore::String::stringWithUTF8Characters(filepath.c_str());
    EdiTestCheckResult fileResult = testMessageParser::parseMessageFromLocalFile(inputPath);
    
    std::map<std::string, EdiTestCheckResult> expectedResults = EdiTestCheckResult::parseExpectedResult(parserEmlPath + "input/expect-results.csv", 1);
    
    std::map<std::string, EdiTestCheckResult>::iterator it = expectedResults.find(filename);
    
    if (it == expectedResults.end()) {
        EXPECT_FALSE(true) << "file expectResult does not exist:" << filename.c_str();
    } else {
        EdiTestCheckResult::checkEmlResult(filename, fileResult, it->second);
    }
    
}

TEST(testFetchMessage, parseEmlHtmlBodyToFile) {
    const std::string root = parserEmlPath + "input/";
    std::vector<std::string> files = EdiTestCheckResult::getAllFiles(root, "eml");
    
    int total = 0;
    int pass = 0;
    for (std::string & file : files) {
        total++;
        std::string filepath = root + file;
        mailcore::String * inputPath = mailcore::String::stringWithUTF8Characters(filepath.c_str());
        testMessageParser::parseEmlHtmlBodyToFile(inputPath);
    }
}
