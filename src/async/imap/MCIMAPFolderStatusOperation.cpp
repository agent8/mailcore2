//
//  MCIMAPFolderStatusOperation.cc
//  mailcore2
//
//  Created by Sebastian on 6/5/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#include "MCIMAPFolderStatusOperation.h"

#include "MCIMAPSession.h"
#include "MCIMAPAsyncConnection.h"
#include "MCIMAPFolderStatus.h"

using namespace mailcore;

IMAPFolderStatusOperation::IMAPFolderStatusOperation()
{
    mStatus = NULL;
}

IMAPFolderStatusOperation::~IMAPFolderStatusOperation()
{
    MC_SAFE_RELEASE(mStatus);
}

void IMAPFolderStatusOperation::main()
{
    ErrorCode error;
    
    session()->session()->loginIfNeeded(&error);
    if (error != ErrorNone) {
        setError(error);
        return;
    }
    //Weicheng: Can't get the message count for some folder with the status command
    //Send the "select" command to get this information
    session()->session()->select(folder(), &error);
    if (error != ErrorNone) {
        setError(error);
        return;
    }
    unsigned int messageCount = session()->session()->lastFolderMessageCount();
//    uint32_t uidNext = session()->session()->uidNext();
//    uint32_t uidValidity = session()->session()->uidValidity();
//    uint64_t modSequence = session()->session()->modSequenceValue();
//    uint32_t firstUnseenUid = session()->session()->firstUnseenUid();
//    bool flags = session()->session()->allowsNewPermanentFlags();
    //================================================================================
    IMAPFolderStatus *status = session()->session()->folderStatus(folder(), &error);
    if (error != ErrorNone) {
        setError(error);
        return;
    }
    
    if (status->messageCount() != messageCount) {
        MCLog("Folder(%s): status(%d) message count is not equal to select(%d)\n",folder()->UTF8Characters(),status->messageCount(),messageCount);
        status->setMessageCount(messageCount);
    }
    
    MC_SAFE_REPLACE_RETAIN(IMAPFolderStatus, mStatus, status);
    setError(error);
}

IMAPFolderStatus * IMAPFolderStatusOperation::status()
{
    return mStatus;
}

