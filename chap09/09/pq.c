#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "pq.h"

#define T pq_t
#define item_t int

typedef struct node_t *link_t;

struct node_t {
    item_t item;
    link_t next;
};

struct _T {
    link_t head;
};
static void *alloc(size_t size);
static link_t newlink(item_t item, link_t next);
static void dellink(link_t *t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(item_t item, link_t next)
{
    link_t t = alloc(sizeof *t);
    t->item  = item;
    t->next  = next;
    return t;
}

static void dellink(link_t *t)
{
    free(*t);
    *t = NULL;
}

T pq_init(size_t n)
{
    (void)n;
    T t     = alloc(sizeof *t);
    t->head = NULL;
    return t;
}

void pq_finalize(T *t)
{
    link_t tmp;

    while ((tmp = (*t)->head) != NULL) {
        (*t)->head = tmp->next;
        dellink(&tmp);
    }

    free(*t);
    *t = NULL;
}

void pq_insert(T t, item_t item)
{
    link_t cur  = t->head;
    link_t prev = NULL;

    while (cur != NULL && item < cur->item) {
        prev = cur;
        cur  = cur->next;
    }

    if (prev == NULL) { /* item should be inserted at head */
        t->head = newlink(item, t->head);
    } else { /* item should be inserted in the middle */
        prev->next = newlink(item, cur);
    }
}

item_t pq_delmax(T t)
{
    assert(!pq_empty(t));
    item_t ret = t->head->item;
    link_t tmp = t->head;
    t->head    = t->head->next;
    dellink(&tmp);
    return ret;
}

int pq_empty(T t)
{
    return t->head == NULL;
}
