#include "MCMessagePart.h"

#include "MCDefines.h"

using namespace mailcore;

MessagePart::MessagePart()
{
    init();
}

MessagePart::MessagePart(MessagePart * other) : AbstractMessagePart(other)
{
    init();
}

void MessagePart::init()
{
}

MessagePart::~MessagePart()
{
}

Object * MessagePart::copy()
{
    return new MessagePart(this);
}

static void * createObject()
{
    return new MessagePart();
}

INITIALIZE(MessagePart)
{
    Object::registerObjectConstructor("mailcore::MessagePart", &createObject);
}
