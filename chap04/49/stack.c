#include <assert.h>
#include <stdlib.h>

#include "stack.h"

#define MAXSIZE 100

static Item buf[MAXSIZE];
static Item *top = buf;
static Item *find(Item n);
int stack_full();
int stack_empty();
void stack_push(Item n);
Item stack_pop();

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
    Item *p;
    assert(!stack_full());

    if ((p = find(n)) != NULL) { /* item exist */
        for (; p != (top - 1); p++) {
            *p = *(p + 1);  /* move element to front */
        }

        *p = n;             /* push the element */
    } else { /* no such element in the stack, we can push it in */
        *top++ = n;
    }
}

Item stack_pop()
{
    assert(!stack_empty());
    return *--top;
}

/**
 * @brief find if the element is in the stack
 *
 * @param n the element to be check
 *
 * @return the pointer to the element if found, else return NULL
 */
static Item *find(Item n)
{
    Item *p = buf;

    for (; p != top; p++) {
        if (*p == n) { /* item exist */
            return p;
        }
    }

    return NULL;
}
