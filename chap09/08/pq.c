#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "pq.h"

#define T      pq_t
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
static item_t delitem(T t, link_t prev, link_t cur);
static void getmax(link_t head, link_t *prevmax, link_t *max);
T pq_init(size_t n);
void pq_finalize(T *t);
int pq_empty(T t);
void pq_insert(T t, item_t item);
item_t pq_delmax(T t);

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
    T tt = *t;
    link_t tmp;

    while ((tmp = tt->head) != NULL) {
        tt->head = tmp->next;
        dellink(&tmp);
    }

    free(tt);
    *t = NULL;
}

int pq_empty(T t)
{
    return t->head == NULL;
}


void pq_insert(T t, item_t item)
{
    t->head = newlink(item, t->head);
}

item_t pq_delmax(T t)
{
    assert(!pq_empty(t));
    item_t ret;
    link_t max = t->head;
    link_t prevmax = NULL;
    /* more  than two item */
    getmax(t->head, &prevmax, &max);
    ret = delitem(t, prevmax, max);
    return ret;
}

static item_t delitem(T t, link_t prev, link_t cur)
{
    item_t ret = cur->item;

    if (prev == NULL) {
        t->head = cur->next;
    } else {
        prev->next = cur->next;
    }

    dellink(&cur);
    return ret;
}

static void getmax(link_t head, link_t *prevmax, link_t *max)
{
    link_t prev = head;
    link_t cur  = head->next;
    *prevmax    = NULL;
    *max        = head;

    for (; cur != NULL; prev = cur, cur = cur->next) {
        if ((*max)->item < cur->item) {
            *prevmax = prev;
            *max     = cur;
        }
    }
}
