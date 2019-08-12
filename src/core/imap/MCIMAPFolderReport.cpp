//
//  MCIMAPFolderReport.cpp
//  mailcore2
//
//  Created by Youbing Yang 2019/08/06.
//  Copyright (c) 2014 MailCore. All rights reserved.
//

#include "MCIMAPFolderReport.h"

using namespace mailcore;

void IMAPFolderReport::init()
{
    mExists = 0;
    mExpunge = 0;
}

IMAPFolderReport::IMAPFolderReport()
{
    init();
}

IMAPFolderReport::IMAPFolderReport(IMAPFolderReport * other)
{
    init();
    setExists(other->getExists());
    setExpunge(other->getExpunge());
}

IMAPFolderReport::~IMAPFolderReport()
{
}

Object * IMAPFolderReport::copy()
{
    return new IMAPFolderReport(this);
}

void IMAPFolderReport::setExists(uint32_t exists)
{
    mExists = exists;
}

uint32_t IMAPFolderReport::getExists()
{
    return mExists;
}

void IMAPFolderReport::setExpunge(uint32_t expunge)
{
    mExpunge = expunge;
}

uint32_t IMAPFolderReport::getExpunge()
{
    return mExpunge;
}

