#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "stack.h"

#define T stack_t

struct T {
    int content[BUFSIZ];
    int *top;
};

static void *alloc(size_t size);
T stack_init();
int stack_empty(T t);
void stack_push(T t, int n);
int stack_pop(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(size);
    return p;
}


T stack_init()
{
    T t     = alloc(sizeof * t);
    t->top  = t->content;
    return t;
}

int stack_empty(T t)
{
    return t->top == t->content;
}

static int stack_full(T t)
{
    return t->top == t->content + BUFSIZ;
}

void stack_push(T t, int n)
{
    assert(!stack_full(t));
    *t->top++ = n;
}

int stack_pop(T t)
{
    assert(!stack_empty(t));
    return *--t->top;
}

void stack_finalize(T t)
{
    free(t);
}
