//
//  EdiTestCheckResult.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/26.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "EdiTestCheckResult.hpp"
#include <fstream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "ediunittest.h"

EdiTestCheckResult::EdiTestCheckResult() : toCount(0), ccCount(0), bccCount(0),
    recvDate(0), htmlParts(0), plainParts(0), attachmentParts(0), inlineAttachmentParts(0), uid(0),
    size(0){
    
}

std::vector<std::string> EdiTestCheckResult::getAllFiles(const std::string &path, const std::string &exten = "*") {

    char cwd[1024];
    getcwd(cwd, 1024);
    std::cout << "Current Working Folder:" << cwd << std::endl;
    std::vector<std::string> list;
    DIR *dp = nullptr;
    struct dirent *dirp = nullptr;
    if ((dp = opendir(path.c_str())) == nullptr) {
        return list;
    }

    while ((dirp = readdir(dp)) != nullptr) {
        if (dirp->d_type == DT_REG) {
            if (exten.compare("*") == 0)
                list.emplace_back(static_cast<std::string>(dirp->d_name));
            else if (std::string(dirp->d_name).find(exten) != std::string::npos)
                list.emplace_back(static_cast<std::string>(dirp->d_name));
        }
    }

    closedir(dp);
    return list;
}

static inline std::vector<std::string> Split(const std::string &s, const char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(std::move(item));
    }
    return elems;
}

std::map<std::string, EdiTestCheckResult> EdiTestCheckResult::parseExpectedResult(const std::string &filename, const int skipLines) {
    std::map<std::string, EdiTestCheckResult> expectedMap;
    std::ifstream readFile(filename, std::ios::in);
    if (!readFile) {
        std::cout << "can not open:" << filename << std::endl;
        return expectedMap;
    }
    int skip = skipLines;
    while (!readFile.eof()) {
        std::string line;
        getline(readFile, line);
        if (skip > 0) {
            skip -= 1;
            continue;
        }

        EdiTestCheckResult checkResult;
        
        std::vector<std::string> s = Split(line, ',');
        if (s.size() > 3) {
            std::string filename = s[0];
            
            checkResult.subject = s[1];
            checkResult.from = s[2];
            checkResult.toCount = std::stoi(s[3]);
            checkResult.ccCount = std::stoi(s[4]);
            checkResult.bccCount = std::stoi(s[5]);
            checkResult.htmlParts = std::stoi(s[6]);
            checkResult.plainParts = std::stoi(s[7]);
            checkResult.attachmentParts = std::stoi(s[8]);
            checkResult.inlineAttachmentParts = std::stoi(s[9]);
            
            expectedMap.insert(std::pair<std::string, EdiTestCheckResult>(filename, checkResult));
        }
    }
    return expectedMap;
}

bool EdiTestCheckResult::checkEmlResult(const std::string & filename, const EdiTestCheckResult & fileResult, const EdiTestCheckResult & expectResult) {
    bool result = true;
    EXPECT_STREQ(fileResult.subject.c_str(), expectResult.subject.c_str());
    EXPECT_STREQ(fileResult.from.c_str(), expectResult.from.c_str());
    EXPECT_EQ(fileResult.ccCount, expectResult.ccCount);
    EXPECT_EQ(fileResult.bccCount, expectResult.bccCount);
    EXPECT_EQ(fileResult.htmlParts, expectResult.htmlParts);
    EXPECT_EQ(fileResult.plainParts, expectResult.plainParts);
    EXPECT_EQ(fileResult.attachmentParts, expectResult.attachmentParts);
    EXPECT_EQ(fileResult.inlineAttachmentParts, expectResult.inlineAttachmentParts);
}

bool EdiTestCheckResult::checkImapHeaderResult(const EdiTestCheckResult & fileResult, const EdiTestCheckResult & expectResult) {
    bool result = true;
    EXPECT_STREQ(fileResult.subject.c_str(), expectResult.subject.c_str());
    EXPECT_STREQ(fileResult.from.c_str(), expectResult.from.c_str());
    EXPECT_EQ(fileResult.ccCount, expectResult.ccCount);
    EXPECT_EQ(fileResult.bccCount, expectResult.bccCount);
    EXPECT_EQ(fileResult.htmlParts, expectResult.htmlParts);
    EXPECT_EQ(fileResult.plainParts, expectResult.plainParts);
    EXPECT_EQ(fileResult.attachmentParts, expectResult.attachmentParts);
    EXPECT_EQ(fileResult.inlineAttachmentParts, expectResult.inlineAttachmentParts);
    EXPECT_EQ(fileResult.uid, expectResult.uid);
}

std::map<uint32_t, EdiTestCheckResult> EdiTestCheckResult::parseImapHeaderResult(const std::string &expectFile, const std::string &parserFile) {
    std::map<uint32_t, EdiTestCheckResult> expectedMap;
    std::ifstream readFile(expectFile, std::ios::in);
    if (!readFile) {
        std::cout << "can not open:" << expectFile << std::endl;
        return expectedMap;
    }
    while (!readFile.eof()) {
        std::string line;
        getline(readFile, line);

        EdiTestCheckResult checkResult;
        
        std::vector<std::string> s = Split(line, ',');
        if (s.size() > 2) {
            std::string filename = s[0];
            
            if (filename.compare(parserFile) == 0) {
                uint32_t uid = std::stoi(s[1]);
                if (uid <= 0) {
                    continue;
                }
                checkResult.uid = uid;
                checkResult.subject = s[2];
                checkResult.from = s[3];
                checkResult.toCount = std::stoi(s[4]);
                checkResult.ccCount = std::stoi(s[5]);
                checkResult.bccCount = std::stoi(s[6]);
                checkResult.htmlParts = std::stoi(s[7]);
                checkResult.plainParts = std::stoi(s[8]);
                checkResult.attachmentParts = std::stoi(s[9]);
                checkResult.inlineAttachmentParts = std::stoi(s[10]);
                expectedMap.insert(std::pair<uint32_t, EdiTestCheckResult>(uid, checkResult));
            }
        }
    }
    return expectedMap;
}
