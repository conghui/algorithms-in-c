#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define T node_t

static T top = NULL;

void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T newnode(Item n, T prev, T next)
{
    T nn = alloc(sizeof * nn);
    nn->entry  = n;
    nn->prev   = prev;
    nn->next   = next;
    return nn;
}

void stack_push(Item n)
{
    T nn      = newnode(n, top, NULL);

    if (top != NULL) {
        top->next = nn;
    }

    top       = nn;
}

Item stack_pop()
{
    assert(!stack_empty());
    T tmp     = top;
    Item r    = top->entry;
    top       = top->prev;

    if (top != NULL) {
        top->next = NULL;
    }

    free(tmp);
    return r;
}

int stack_empty()
{
    return top == NULL;
}

void stack_print()
{
    T cur;

    for (cur = top; cur != NULL; cur = cur->prev) {
        printf("%d ", cur->entry);
    }
}

void stack_clear()
{
    while (!stack_empty()) {
        stack_pop();
    }
}
