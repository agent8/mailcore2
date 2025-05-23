//
//  MCIMAPCapabilityOperation.cpp
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/4/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#include "MCIMAPCapabilityOperation.h"

#include "MCIMAPSession.h"
#include "MCIMAPAsyncConnection.h"

using namespace mailcore;

IMAPCapabilityOperation::IMAPCapabilityOperation()
{
    mCapabilities = NULL;
    mForceLogin = false;
}

IMAPCapabilityOperation::~IMAPCapabilityOperation()
{
    MC_SAFE_RELEASE(mCapabilities);
}

IndexSet * IMAPCapabilityOperation::capabilities()
{
    return mCapabilities;
}

void IMAPCapabilityOperation::setForceLogin(bool forceLogin){
    this->mForceLogin = forceLogin;
}

bool IMAPCapabilityOperation::forceLogin(){
    return mForceLogin;
}

void IMAPCapabilityOperation::main()
{
    ErrorCode error = ErrorNone;
    if (mForceLogin) {
        session()->session()->loginIfNeeded(&error);
        if (error != ErrorNone) {
            setError(error);
            return;
        }
        mCapabilities = session()->session()->capability(&error);
    } else {
        mCapabilities = session()->session()->storedCapabilities();
        if (mCapabilities == NULL) {
            mCapabilities = session()->session()->capability(&error);
            if (mCapabilities == NULL) {
                session()->session()->loginIfNeeded(&error);
                if (error != ErrorNone) {
                    setError(error);
                    return;
                }
                mCapabilities = session()->session()->capability(&error);
            }
        }
    }
    
    MC_SAFE_RETAIN(mCapabilities);
    setError(error);
}

