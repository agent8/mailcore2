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

mailcore::IMAPSession * test_imap_sync_session(const std::string & email, const std::string & passwd, const std::string & host, bool outlog=true);

#endif /* testMailcoreUtils_hpp */
