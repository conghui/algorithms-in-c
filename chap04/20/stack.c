#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#include "stack.h"

#define T Item
#undef BUFSIZ
#define BUFSIZ 5
static T buf[BUFSIZ];
static T *top = buf;

static int STACK_full();
static int STACK_empty();
void STACK_push(T entry);
T STACK_pop();
void error(const char *fmt, ...);

static int STACK_full()
{
    return top == buf + BUFSIZ - 1;
}

static int STACK_empty()
{
    return top == buf;
}

void STACK_push(T entry)
{
    if (STACK_full()) {
        fprintf(stderr, "stack is full\n");
        exit(EXIT_FAILURE);
    }

    *top++ = entry;
}

T STACK_pop()
{
    if (STACK_empty()) {
        error("stack is empty\n");
    }

    return *--top;
}

void error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    exit(EXIT_FAILURE);
    va_end(ap);
}
