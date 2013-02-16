#include <stdlib.h>
#include <assert.h>
#include "alloc.h"

void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}
