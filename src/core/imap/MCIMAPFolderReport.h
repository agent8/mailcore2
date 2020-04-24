//
//  MCIMAPFolderReport.h
//  mailcore2
//
//  Created by Youbing Yang 2019/08/06.
//  Copyright (c) 2014 MailCore. All rights reserved.
//

#ifndef MAILCORE_MCIMAPFolderReport_H

#define MAILCORE_MCIMAPFolderReport_H

#include <MailCore/MCBaseTypes.h>
#include <MailCore/MCMessageConstants.h>

#ifdef __cplusplus

namespace mailcore {
    
    class MAILCORE_EXPORT IMAPFolderReport : public Object {
    public:
        IMAPFolderReport();
        virtual ~IMAPFolderReport();
        
        virtual void setExists(uint32_t exists);
        virtual uint32_t getExists();
        
        virtual void setExpunge(uint32_t expunge);
        virtual uint32_t getExpunge();
        
    public:
        IMAPFolderReport(IMAPFolderReport * other);
        virtual Object * copy();		
        
    private:
        uint32_t mExists;
        uint32_t mExpunge;
        void init();
    };
    
}

#endif

#endif

