//
//  testMailcoreUtils.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/11.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "testMailcoreUtils.hpp"

mailcore::IMAPSession * test_imap_sync_session(const std::string & email, const std::string & passwd, const std::string & host, bool outlog) {
    mailcore::IMAPSession * imapSession = new mailcore::IMAPSession();
    imapSession->setHostname(mailcore::String::uniquedStringWithUTF8Characters(host.c_str()));
    imapSession->setPort(993);
    imapSession->setUsername(mailcore::String::uniquedStringWithUTF8Characters(email.c_str()));
    
    if (!passwd.empty()) {
        imapSession->setPassword(mailcore::String::uniquedStringWithUTF8Characters(passwd.c_str()));
    }/* else if (!account->accessToken.empty()) {
        imapSession->setOAuth2Token(mailcore::String::uniquedStringWithUTF8Characters(account->accessToken.c_str()));
        imapSession->setAuthType(mailcore::AuthTypeXOAuth2);
    }*/
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
