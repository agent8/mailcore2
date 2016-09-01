#ifndef MAILCORE_MCIMAPMULTIPART_H

#define MAILCORE_MCIMAPMULTIPART_H

#include <MailCore/MCAbstractMultipart.h>

#ifdef __cplusplus

namespace mailcore {
    
    class MAILCORE_EXPORT IMAPMultipart : public AbstractMultipart {
    public:
        IMAPMultipart();
        virtual ~IMAPMultipart();
        
    public: // subclass behavior
        IMAPMultipart(IMAPMultipart * other);
        virtual Object * copy();
        virtual HashMap * serializable();
        virtual void importSerializable(HashMap * serializable);
        
    private:
        void init();
    };
    
}

#endif

#endif
