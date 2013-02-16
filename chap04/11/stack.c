#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define T Item

static Item *buf = NULL;
static Item *top = NULL;
static size_t N;

void stack_init(size_t size)
{
    buf = malloc(sizeof * buf * size);
    assert(buf);
    top = buf;
    N   = size;
}

void stack_free()
{
    free(buf);
}

void stack_push(Item n)
{
    assert(!stack_full());
    *top++ = n;
}

int stack_full()
{
    return top == buf + N - 1;
}

int stack_empty()
{
    return top == buf;
}

Item stack_pop()
{
    return *--top;
}

size_t stack_count()
{
    return top - buf;
}
