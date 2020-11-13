这里用到测试的框架是gtest，源码的路径是https://github.com/google/googletest，已经将源码做了编译，感兴趣可以去看看源码。

需要修改的地方：
1. 如果测试需要用到本地的路径文件，可以将本地路径设置到xcode工程中，然后就可以使用相对路径来访问对应的文件。
选中左上角的editest->Edit Scheme->Run->Options->选中Working Directory->定位到自己本地的mailcore2目录（例如：/Users/xulei/Desktop/git/mailcore2）
2. 根据自己的需求来添加测试用例，具体可参考main.cpp上面的注释部分的测试用例。