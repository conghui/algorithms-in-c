#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "queue.h"

#define T queue_t

#define L link_t
typedef struct L *L;

struct L { /* a node  */
    int entry;
    L next;
};

struct T {
    L head;
    L tail;
};
static void *alloc(size_t size);
static L newnode(int n, L next);
static void delnode(L l);
T queue_init();
void queue_finalize(T t);
int queue_empty(T t);
void queue_push(T t, int n);
int queue_pop(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
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

T queue_init()
{
    T t     = alloc(sizeof * t);
    t->head = NULL;
    t->tail = NULL;
    return t;
}

void queue_finalize(T t)
{
    assert(t);

    while (t->head != NULL) {
        L tmp   = t->head;
        t->head = tmp->next;
        delnode(tmp);
    }

    free(t);
}

int queue_empty(T t)
{
    return t->head == NULL && t->tail == NULL;
}

void queue_push(T t, int n)
{
    if (queue_empty(t)) {
        t->head = t->tail = newnode(n, NULL);
    } else {
        t->tail->next = newnode(n, t->tail->next);
        t->tail = t->tail->next;
    }
}

int queue_pop(T t)
{
    L tmp;
    int item;
    assert(!queue_empty(t));
    item = t->head->entry;

    if (t->head == t->tail) { /* only one item */
        tmp   = t->head;
        t->head = NULL;
        t->tail = NULL;
    } else {
        tmp     = t->head;
        t->head = tmp->next;
    }

    delnode(tmp);
    return item;
}
