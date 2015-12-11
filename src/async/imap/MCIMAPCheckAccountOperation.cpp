//
//  MCIMAPCheckAccountOperation.cc
//  mailcore2
//
//  Created by DINH Viêt Hoà on 1/12/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#include "MCIMAPCheckAccountOperation.h"

#include "MCIMAPAsyncConnection.h"
#include "MCIMAPSession.h"

using namespace mailcore;

IMAPCheckAccountOperation::IMAPCheckAccountOperation()
{
    mLoginResponse = NULL;
}

IMAPCheckAccountOperation::~IMAPCheckAccountOperation()
{
    MC_SAFE_RELEASE(mLoginResponse);
}


void IMAPCheckAccountOperation::main()
{
    ErrorCode error;
    session()->session()->connectIfNeeded(&error);
    if (error == ErrorNone){
        session()->session()->login(&error);
    }
    mLoginResponse = session()->session()->getResponse();
    MC_SAFE_RETAIN(mLoginResponse);
    setError(error);
}

String * IMAPCheckAccountOperation::getLoginResponse()
{
    return mLoginResponse;
}
