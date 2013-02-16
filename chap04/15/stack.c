#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "stack.h"


static char *buf[BUFSIZ];
static char **top = buf;


void stack_push(const char *item)
{
    if (stack_full()) {
        error("stack is full");
    }

    char *p = malloc(strlen(item) + 1);
    strcpy(p, item);
    *top++ = p;
}

int stack_full()
{
    return top == buf + BUFSIZ - 1;
}

void error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
    va_end(ap);
}

int stack_empty()
{
    return top == buf;
}

void stack_pop(char *store)
{
    if (stack_empty()) {
        error("stack is empty");
    }

    strcpy(store, *--top);
    free(*top);
}
