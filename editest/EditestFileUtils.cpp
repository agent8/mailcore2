//
//  EditestFileUtils.cpp
//  editest
//
//  Created by 徐雷 on 2020/8/20.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "EditestFileUtils.hpp"
#include <fstream>

std::string EditestFileUtils::getStringFromLocalFile(const char * filepath) {
    std::string result;
    if (filepath != nullptr) {
        try {
            std::ifstream testInput;
            testInput.open(filepath, std::ios::in | std::ios::binary);
            
            if (testInput.is_open()) {
                testInput.seekg (0, std::ios::end);
                long length = testInput.tellg();
                testInput.seekg (0, std::ios::beg);
                
                char * fileData = new char [length+1];
                
                testInput.read (fileData, length);
                
                fileData[length] = 0;
                
                testInput.close();
                
                result = fileData;
                
                delete [] fileData;
            }
            
        } catch (const std::exception & e) {
            //std::cout << "failed to parse test input for " << e.what() << std::endl;
        } catch (...) {
            //std::cout << "failed to parse test input for other" << std::endl;
        }
    }
    
    return result;
}
