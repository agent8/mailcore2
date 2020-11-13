//
//  testEdiAccount.h
//  editest
//
//  Created by 徐雷 on 2020/8/11.
//  Copyright © 2020 MailCore. All rights reserved.
//

#ifndef testEdiAccount_h
#define testEdiAccount_h
#include <string>

class testEdiAccount {
    
public:
    std::string email;
    std::string passwd;
    std::string host;
    int port;
    bool isGmail;
    std::string accessToken;
    std::string refreshToken;
};

#endif /* testEdiAccount_h */
