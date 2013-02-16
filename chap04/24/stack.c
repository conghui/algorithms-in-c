#include <assert.h>
#include "stack.h"

#undef BUFSIZ
#define BUFSIZ 10

static Item buf[BUFSIZ];
static Item *top1 = buf;            /* the first element from the begining */
static Item *top2 = buf + BUFSIZ - 1;   /* the first element from the end */

void stack1_push(Item n)
{
    assert(!stack_full());
    *top1++ = n;
}

void stack2_push(Item n)
{
    assert(!stack_full());
    *top2-- = n;
}

Item stack1_pop()
{
    assert(!stack1_empty());
    return *--top1;
}

Item stack2_pop()
{
    assert(!stack2_empty());
    return *++top2;
}

int stack_full()
{
    return top1 > top2;
}

int stack1_empty()
{
    return top1 == buf;
}

int stack2_empty()
{
    return top2 == buf + BUFSIZ - 1;
}
