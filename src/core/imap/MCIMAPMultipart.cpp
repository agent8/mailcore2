#include "MCIMAPMultipart.h"

#include "MCDefines.h"

using namespace mailcore;

IMAPMultipart::IMAPMultipart()
{
    init();
}

IMAPMultipart::IMAPMultipart(IMAPMultipart * other) : AbstractMultipart(other)
{
    init();
}

IMAPMultipart::~IMAPMultipart()
{
}

Object * IMAPMultipart::copy()
{
    return new IMAPMultipart(this);
}

void IMAPMultipart::init()
{

}

HashMap * IMAPMultipart::serializable()
{
    HashMap * result = AbstractMultipart::serializable();
    if (partID() != NULL) {
        result->setObjectForKey(MCSTR("partID"), partID());
    }
    return result;
}

void IMAPMultipart::importSerializable(HashMap * serializable)
{
    AbstractMultipart::importSerializable(serializable);
    String * partID = (String *) serializable->objectForKey(MCSTR("partID"));
    setPartID(partID);
}

static void * createObject()
{
    return new IMAPMultipart();
}

INITIALIZE(IMAPMultipart)
{
    Object::registerObjectConstructor("mailcore::IMAPMultipart", &createObject);
}

