#include "MCIMAPMessagePart.h"

#include "MCDefines.h"

using namespace mailcore;

IMAPMessagePart::IMAPMessagePart()
{
    init();
}

IMAPMessagePart::IMAPMessagePart(IMAPMessagePart * other) : AbstractMessagePart(other)
{
    init();
}

IMAPMessagePart::~IMAPMessagePart()
{
}

Object * IMAPMessagePart::copy()
{
    return new IMAPMessagePart(this);
}

void IMAPMessagePart::init()
{
}


HashMap * IMAPMessagePart::serializable()
{
    HashMap * result = AbstractMessagePart::serializable();
    if (partID() != NULL) {
        result->setObjectForKey(MCSTR("partID"), partID());
    }
    return result;
}

void IMAPMessagePart::importSerializable(HashMap * serializable)
{
    AbstractMessagePart::importSerializable(serializable);
    String * partID = (String *) serializable->objectForKey(MCSTR("partID"));
    setPartID(partID);
}

static void * createObject()
{
    return new IMAPMessagePart();
}

INITIALIZE(IMAPMessagePart)
{
    Object::registerObjectConstructor("mailcore::IMAPMessagePart", &createObject);
}
