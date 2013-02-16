#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "stackList.h"

#define T stack_t

static T top = NULL;

static void *alloc(size_t size);
static void error(const char *fmt, ...);

T stackList_newnode(int n)
{
    T nn      = alloc(sizeof * nn);
    nn->entry = n;
    nn->next  = NULL;
    return nn;
}


void stackList_push(int n)
{
    T nn = stackList_newnode(n);

    if (top == NULL) {
        top = nn;
    } else {
        nn->next = top;
        top      = nn;
    }
}

int stackList_pop()
{
    assert(!stackList_empty());
    T cur;
    int entry;
    entry = top->entry;
    cur   = top;
    top   = top->next;
    free(cur);
    return entry;
}

int stackList_count()
{
    int count = 0;
    T cur;

    for (cur = top; cur != NULL; cur = cur->next) {
        count++;
    }

    return count;
}

int stackList_empty()
{
    if (top == NULL) {
        return 1;
    }

    return 0;
}

static void *alloc(size_t size)
{
    void *p = malloc(size);

    if (p == NULL) {
        error("out of memory");
    }

    return p;
}

static void error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
    va_end(ap);
}
