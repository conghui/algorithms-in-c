#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "stackArray.h"

#define T Item

static T buf[BUFSIZ];
static T *top = buf;

int stackArray_isfull()
{
    return top == buf + BUFSIZ - 1;
}

int stackArray_isempty()
{
    return top == buf;
}

void stackArray_push(T n)
{
    assert(!stackArray_isfull());
    *top++ = n;
}

T stackArray_pop()
{
    assert(!stackArray_isempty());
    return *--top;
}

int stackArray_count()
{
    return top - buf;
}
