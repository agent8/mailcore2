#include "MCMultipart.h"

#include "MCDefines.h"

using namespace mailcore;

Multipart::Multipart()
{
    init();
}

Multipart::Multipart(Multipart * other) : AbstractMultipart(other)
{
    init();
}

void Multipart::init()
{
}

Multipart::~Multipart()
{
}

Object * Multipart::copy()
{
    return new Multipart(this);
}

static void * createObject()
{
    return new Multipart();
}

INITIALIZE(Multipart)
{
    Object::registerObjectConstructor("mailcore::Multipart", &createObject);
}
