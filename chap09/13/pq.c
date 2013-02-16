#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "pq.h"

#define T      pq_t
#define item_t int

struct _T {
    item_t *content;
    size_t size;
    size_t capacity;
};
static void *alloc(size_t size);
static int full(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T pq_init(size_t n)
{
    T t         = alloc(sizeof *t);
    t->content  = alloc(n * sizeof *t->content);
    t->capacity = n;
    t->size     = 0;
    return t;
}

void pq_finalize(T *t)
{
    T tt = *t;
    free(tt->content);
    free(tt);
    *t = NULL;
}

int pq_empty(T t)
{
    return t->size == 0;
}

static int full(T t)
{
    return t->size == t->capacity;
}

void pq_insert(T t, item_t item)
{
    assert(!full(t));
    int i = t->size;

    for (; i > 0 && item < t->content[i-1]; i--) {
        t->content[i] = t->content[i-1];
    }

    t->content[i] = item;
    t->size++;
}

item_t pq_delmax(T t)
{
    assert(!pq_empty(t));
    return t->content[--t->size];
}
