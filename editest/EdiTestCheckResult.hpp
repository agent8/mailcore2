//
//  EdiTestCheckResult.hpp
//  editest
//
//  Created by 徐雷 on 2020/8/26.
//  Copyright © 2020 MailCore. All rights reserved.
//

#ifndef EdiTestCheckResult_hpp
#define EdiTestCheckResult_hpp

#include <iostream>
#include <map>
#include <string>

class EdiTestCheckResult {
public:
    EdiTestCheckResult();
    static std::vector<std::string> getAllFiles(const std::string &root, const std::string &exten);
    static std::map<std::string, EdiTestCheckResult> parseExpectedResult(const std::string &filename, const int skipLines = 1);
    static bool checkEmlResult(const std::string & filename, const EdiTestCheckResult & fileResult, const EdiTestCheckResult & expectResult);
    static bool checkImapHeaderResult(const EdiTestCheckResult & fileResult, const EdiTestCheckResult & expectResult);
    static std::map<uint32_t, EdiTestCheckResult> parseImapHeaderResult(const std::string &expectFile, const std::string &parserFile);
public:
    std::string subject;
    std::string from;
    int toCount;
    int ccCount;
    int bccCount;
    int recvDate;
    int htmlParts;
    int plainParts;
    int attachmentParts;
    int inlineAttachmentParts;
    
    uint32_t uid;
    uint32_t size;
    int mainPart;
    
};

#endif /* EdiTestCheckResult_hpp */
