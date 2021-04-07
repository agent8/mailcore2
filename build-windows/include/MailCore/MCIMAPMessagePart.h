#ifndef MAILCORE_IMAPMESSAGEPART_H

#define MAILCORE_IMAPMESSAGEPART_H

#include <MailCore/MCAbstractMessagePart.h>

#ifdef __cplusplus

namespace mailcore {
    
    class MAILCORE_EXPORT IMAPMessagePart : public AbstractMessagePart {
    public:
        IMAPMessagePart();
        virtual ~IMAPMessagePart();
        
    public: // subclass behavior
        IMAPMessagePart(IMAPMessagePart * other);
        virtual Object * copy();
        virtual HashMap * serializable();
        virtual void importSerializable(HashMap * serializable);
        
    private:
        void init();
    };
    
}

#endif

#endif
