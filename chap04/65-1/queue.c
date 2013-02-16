#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "queue.h"

#define T queue_t

struct T {
    int content[BUFSIZ];
    size_t size;
    size_t head;
    size_t tail;
};
static void *alloc(size_t size);
static int queue_full(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T queue_init()
{
    T t     = alloc(sizeof * t);
    t->size = 0;
    t->head = 0;
    t->tail = 0;
    return t;
}

void queue_finalize(T t)
{
    assert(t);
    free(t);
}

int queue_empty(T t)
{
    return t->size == 0;
}

static int queue_full(T t)
{
    return t->size == BUFSIZ;
}

void queue_push(T t, int n)
{
    size_t next;
    assert(!queue_full(t));
    next             = (t->tail + 1) % BUFSIZ;
    t->content[t->tail] = n;
    t->tail          = next;
    t->size         += 1;
}

int queue_pop(T t)
{
    size_t next;
    int     reval;
    assert(!queue_empty(t));
    next = (t->head + 1) % BUFSIZ;
    reval   = t->content[t->head];
    t->head = next;
    t->size--;
    return reval;
}
