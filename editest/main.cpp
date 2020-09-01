//
//  main.cpp
//  editest
//
//  Created by xulei on 2020/8/6.
//  Copyright © 2020 MailCore. All rights reserved.
//

#include "ediunittest.h"

//int Add(int a, int b)
//{
//    return a+b;
//}
//
//TEST(testCase, test0)
//{
//    EXPECT_EQ(14, Add(4, 10));
//}
//
//TEST(testCase, test1)
//{
//    EXPECT_EQ(6, Add(5, 7));
//}
//
//TEST(testCase, test2)
//{
//    EXPECT_EQ(28, Add(8, 10)) << "bugs";
//}

int main(int argc, const char * argv[]) {
    
 //   testing::GTEST_FLAG(output) = "xml:"; //generate a xml file
    char * argument[10];
    argument[0] = "editest";
    //if just test one case, add "--gtest_filter=testCase.*" to command line argument
    argument[1] = "--gtest_filter=testMessageParserLibetpan.*";
    argument[2] = "–-gtest_output=xml";
    argc = 3;
    
    testing::InitGoogleTest(&argc, (char **)argument);
    return RUN_ALL_TESTS();
}
