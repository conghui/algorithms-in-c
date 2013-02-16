#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "stack.h"

#include "complex.h"

#define T stack_t

typedef struct node_t *link;

struct node_t {
    complex_t entry;
    link      next;
};

struct T {
    link head;
};
static void *alloc(size_t size);
static link newlink(complex_t n, link next);
static void dellink(link *l);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link newlink(complex_t n, link next)
{
    link l   = alloc(sizeof * l);
    l->entry = complex_copy(n);
    l->next  = next;
    return l;
}

static void dellink(link *l)
{
    complex_finalize(&(*l)->entry);
    free(*l);
    *l = NULL;
}

T stack_init()
{
    T t     = alloc(sizeof * t);
    t->head = NULL;
    return t;
}
int stack_empty(T t)
{
    return t->head == NULL;
}

void stack_push(T t, complex_t n)
{
    t->head = newlink(n, t->head);
}

complex_t stack_pop(T t)
{
    complex_t reval = complex_copy(t->head->entry);
    link tmp        = t->head;
    t->head         = t->head->next;
    dellink(&tmp);
    return reval;
}

void stack_finalize(T *t)
{
    while (!stack_empty(*t)) {
        stack_pop(*t);
    }

    free(*t);
    *t = NULL;
}
