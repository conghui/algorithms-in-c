#include <stdlib.h>
#include <assert.h>

#include "randlist.h"

#define MAXSIZE 100

static Item buf[MAXSIZE];
static Item *tail = buf;
static size_t rand_int(size_t n);

int randlist_empty()
{
    return tail == buf;
}

int randlist_full()
{
    return tail == buf + MAXSIZE;
}

void randlist_push(Item n)
{
    assert(!randlist_full());
    *tail++ = n;
}

int randlist_pop()
{
    size_t idx;
    Item rt;
    assert(!randlist_empty());
    idx = rand_int(tail - buf);
    rt       = buf[idx];
    buf[idx] = *--tail;
    return rt;
}

static size_t rand_int(size_t n)
{
    return rand() % n;
}
