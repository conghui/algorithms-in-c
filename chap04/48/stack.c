#include <assert.h>

#include "stack.h"

#define MAXSIZE 100

static Item buf[MAXSIZE];
static Item *top = buf;
static int find(Item n);

int stack_full()
{
    return top == buf + MAXSIZE;
}

int stack_empty()
{
    return top == buf;
}

void stack_push(Item n)
{
    assert(!stack_full());

    if (find(n)) { /* item exist, just return */
        return;
    }

    /* no such element in the stack, we can push it in */
    *top++ = n;
}

Item stack_pop()
{
    assert(!stack_empty());
    return *--top;
}

static int find(Item n)
{
    Item *p = buf;

    for (; p != top; p++) {
        if (*p == n) { /* item exist */
            return 1;
        }
    }

    return 0;
}
