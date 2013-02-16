#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "pq.h"

#define T PQ_t
#define item_t int

struct _T {
    item_t *content;
    item_t *tail;
    size_t capacity;
};
static void *alloc(size_t size);
static void swap(item_t *a, item_t *b);
static int full(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T PQ_init(size_t n)
{
    T t        = alloc(sizeof *t);
    t->content = alloc(n * sizeof *t->content);
    t->capacity = n;
    t->tail     = t->content;
    return t;
}

void PQ_finalize(T *t)
{
    free((*t)->content);
    free(*t);
    *t = NULL;
}

int PQ_empty(T t)
{
    return t->tail == t->content;
}

void PQ_insert(T t, item_t item)
{
    assert(!full(t));
    *t->tail++ = item;
}

item_t PQ_delmax(T t)
{
    item_t *pmax = t->content;
    item_t *p;

    for (p = t->content + 1; p != t->tail; p++) {
        if (*pmax < *p) {
            pmax = p;
        }
    }

    swap(pmax, --t->tail);
    return *t->tail;
}

static void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

static int full(T t)
{
    return t->tail == t->content + t->capacity;
}
