#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define T node_t

static T top = NULL;


void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T newnode(Item n, T next)
{
    T nn      = alloc(sizeof * nn);
    nn->next  = next;
    nn->entry = n;
    return nn;
}

void stack_push(Item n)
{
    top = newnode(n, top);
}

Item stack_pop()
{
    assert(!stack_empty());
    Item r   = top->entry;
    T    tmp = top;
    top      = top->next;
    free(tmp);
    return r;
}

int stack_empty()
{
    return top == NULL;
}

void stack_clear()
{
    while (!stack_empty()) {
        stack_pop();
    }
}

void stack_print()
{
    T cur;

    for (cur = top; cur != NULL; cur = cur->next) {
        printf("%d ", cur->entry);
    }

    putchar('\n');
}
