#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static int buf[BUFSIZ];
static int *top = buf;

void stack_push(int c)
{
    if (stack_full()) {
        fprintf(stderr, "stack is full\n");
        exit(EXIT_FAILURE);
    }

    *top++ = c;
}

int stack_full()
{
    return top == buf + BUFSIZ - 1;
}

int stack_pop()
{
    if (stack_empty()) {
        fprintf(stderr, "stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return *--top;
}

int stack_empty()
{
    return top == buf;
}
