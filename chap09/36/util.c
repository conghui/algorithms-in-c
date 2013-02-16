#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "glovar.h"
#include "util.h"

void print(item_t *x)
{
    printf("%3d ", *x);
}

item_t randNum()
{
    return rand() % MAX;
}

void for_each(Iterator first, Iterator last, Function f)
{
    while (first != last) {
        f(first++);
    }
}

void generate(Iterator first, Iterator last, Generator gen)
{
    while (first != last) {
        *first++ = gen();
    }
}

void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}


int comp(const void *l, const void *r)
{
    return *(item_t *)l - *(item_t *)r;
}

int lt(item_t a, item_t b)
{
    compcnt++;
    return a < b;
}

int gt(item_t a, item_t b)
{
    compcnt++;
    return a > b;
}
void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}
