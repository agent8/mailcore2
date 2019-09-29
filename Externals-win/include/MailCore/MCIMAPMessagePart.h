#ifndef MAILCORE_IMAPMESSAGEPART_H

#define MAILCORE_IMAPMESSAGEPART_H

#include <MailCore/MCAbstractMessagePart.h>

#ifdef __cplusplus

namespace mailcore {
    
    class MAILCORE_EXPORT IMAPMessagePart : public AbstractMessagePart {
    public:
        IMAPMessagePart();
        virtual ~IMAPMessagePart();
        
        virtual void setPartID(String * partID);
        virtual String * partID();
        virtual void setSize(unsigned int size);
        virtual unsigned int size();
    public: // subclass behavior
        IMAPMessagePart(IMAPMessagePart * other);
        virtual Object * copy();
        virtual HashMap * serializable();
        virtual void importSerializable(HashMap * serializable);
        
    private:
        String * mPartID;
        unsigned int mSize;
        void init();
    };
    
}

#endif

#endif
