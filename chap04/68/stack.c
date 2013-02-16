#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "stack.h"

#define T stack_t

#define L link
typedef struct L *L;
struct L {
    int entry;
    L next;
};

struct T {
    L head;
};
static void *alloc(size_t size);
static L newnode(int n, L next);
static void delnode(L l);
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

static L newnode(int n, L next)
{
    L nn      = alloc(sizeof * nn);
    nn->entry = n;
    nn->next  = next;
    return nn;
}

static void delnode(L l)
{
    free(l);
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

void stack_push(T t, int n)
{
    t->head = newnode(n, t->head);
}

int stack_pop(T t)
{
    int reval;
    L tmp;
    assert(!stack_empty(t));
    reval = t->head->entry;
    tmp     = t->head;
    t->head = tmp->next;
    delnode(tmp);
    return reval;
}

void stack_finalize(T t)
{
    L tmp;

    while ((tmp = t->head) != NULL) {
        t->head = tmp->next;
        delnode(tmp);
    }

    free(t);
}
