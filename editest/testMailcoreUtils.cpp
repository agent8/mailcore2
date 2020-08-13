//
//  testMailcoreUtils.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/11.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "testMailcoreUtils.hpp"
#include "nlohmann/json.hpp"
#include <iosfwd>
#include <fstream>
#include <iostream>
#include <sstream>

mailcore::IMAPSession * testImapSession(const testEdiAccount * account, bool outlog) {
    mailcore::IMAPSession * imapSession = new mailcore::IMAPSession();
    imapSession->setHostname(mailcore::String::uniquedStringWithUTF8Characters(account->host.c_str()));
    imapSession->setPort(993);
    imapSession->setUsername(mailcore::String::uniquedStringWithUTF8Characters(account->email.c_str()));
    
    if (!account->passwd.empty()) {
        imapSession->setPassword(mailcore::String::uniquedStringWithUTF8Characters(account->passwd.c_str()));
    } else if (!account->accessToken.empty()) {
        imapSession->setOAuth2Token(mailcore::String::uniquedStringWithUTF8Characters(account->accessToken.c_str()));
        imapSession->setAuthType(mailcore::AuthTypeXOAuth2);
    }
    imapSession->setVoIPEnabled(false);
    //unsigned int connType = EmailProviderManager::getImapConnType(account->connType);
    int connType = 2;
    if (connType == 2) {
        imapSession->setConnectionType(mailcore::ConnectionTypeTLS);
    } else if (connType == 1) {
        imapSession->setConnectionType(mailcore::ConnectionTypeStartTLS);
    } else {
        imapSession->setConnectionType(mailcore::ConnectionTypeClear);
    }
    imapSession->setTimeout(60);
    
    if (outlog) {
//        mailcore::ConnectionLogger * logger = new TestConnectionLogger();
//        imapSession->setConnectionLogger(logger);
    }
    
    //    This is important.
    mailcore::IMAPIdentity * clientIdentity = new mailcore::IMAPIdentity();
    clientIdentity->setName(MCSTR("Edison Mail"));
    clientIdentity->setVendor(MCSTR("Edison"));
    clientIdentity->setVersion(MCSTR("1.0.0"));
    imapSession->setClientIdentity(clientIdentity);
    clientIdentity->release();
    
    return imapSession;
}

const char * getAccountDataByPath(const char * filename) {
    
    char * testAccountData = nullptr;
    std::string filepath(filename);
    try {
        std::ifstream inputStream;
        
        inputStream.open(filepath, std::ios::in | std::ios::binary);
        
        if (inputStream.is_open()) {
            
            inputStream.seekg (0, std::ios::end);
            long length = inputStream.tellg();
            inputStream.seekg (0, std::ios::beg);
            
            testAccountData = new char [length+1];
            
            inputStream.read (testAccountData, length);
            testAccountData[length] = 0;
            
            inputStream.close();
        } else {
            std::cout << "failed to open the file: " << filepath << std::endl;
        }
        
    } catch (std::exception e) {
        std::cout << "failed to parse test input for " << e.what() << std::endl;
    } catch (...) {
        std::cout << "failed to parse test input for other" << std::endl;
    }
    
    return testAccountData;
}

testEdiAccount * testReadAccountFromFile(const char * acctFilename) {
    testEdiAccount * account = nullptr;
    try {
        const char * acctData = getAccountDataByPath(acctFilename);
        if (acctData) {
            nlohmann::json jdata = nlohmann::json::parse(acctData);
            if (jdata.find("__cls") != jdata.end()) {
                if (jdata.at("__cls").get<std::string>() == "Account") {
                    account = new testEdiAccount();
                    
                    if (jdata.find("emailAddress") != jdata.end()) {
                        account->email = jdata["emailAddress"];
                    }
                    if (jdata.find("provider") != jdata.end()) {
                        std::string strProvider = jdata["provider"];
                        if (strProvider.compare("gmail") == 0) {
                            account->isGmail = true;
                        } else {
                            account->isGmail = false;
                        }
                    }
                    if (jdata.find("settings") != jdata.end()) {
                        auto jsetting = jdata["settings"];
                        if (jsetting.find("access_token") != jsetting.end()) {
                            account->accessToken = jsetting["access_token"];
                        }
                        if (jsetting.find("imap_host") != jsetting.end()) {
                            account->host = jsetting["imap_host"];
                        }
                        if (jsetting.find("refresh_token") != jsetting.end()) {
                            account->refreshToken = jsetting["refresh_token"];
                        }
                        if (jsetting.find("imap_password") != jsetting.end()) {
                            account->passwd = jsetting["imap_password"];
                        }
                        if (jsetting.find("imap_port") != jsetting.end()) {
                            account->port = jsetting["imap_port"];
                        }
                    }
                    
                }
            }
        } else {
            std::cout << "Failed to get account data." << std::endl;
        }
    } catch (std::exception e) {
        std::cout << __FILE__ << "(" << __LINE__ << ") " << "Failed parse json:" << e.what() << std::endl;
    }
    return account;
}
