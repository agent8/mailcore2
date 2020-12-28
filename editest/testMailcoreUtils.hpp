//
//  testMailcoreUtils.hpp
//  editest
//
//  Created by 徐雷 on 2020/8/11.
//  Copyright © 2020 MailCore. All rights reserved.
//

#ifndef testMailcoreUtils_hpp
#define testMailcoreUtils_hpp
#include <MailCore/MailCore.h>
#include <iostream>
#include "testEdiAccount.h"

mailcore::IMAPSession * testImapSession(const testEdiAccount * account, bool outlog=true);
testEdiAccount * testReadAccountFromFile(const char * acctFilename);

#endif /* testMailcoreUtils_hpp */
