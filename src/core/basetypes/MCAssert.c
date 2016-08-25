#include "MCAssert.h"

#include <stdio.h>
#include <stdlib.h>

#define MCDisabledAssert 1
void MCAssertInternal(const char * filename, unsigned int line, int cond, const char * condString)
{
    if (cond || MCDisabledAssert) {
        return;
    }
    
    fprintf(stderr, "%s:%u: assert %s\n", filename, line, condString);
    abort();
}
