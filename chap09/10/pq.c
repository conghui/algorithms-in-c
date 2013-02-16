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
    link_t sorted;
    link_t unsorted;
};

static void *alloc(size_t size);
static link_t newlink(item_t item, link_t next);
static void dellink(link_t *t);
static void dellist(link_t *t);
static item_t del(T t, link_t target);
static void sort(T t);
T pq_init(size_t n);
void pq_finalize(T *t);
void pq_insert(T t, item_t item);
item_t pq_delmax(T t);
int pq_empty(T t);
int pq_delmax(T t);

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
    T t         = alloc(sizeof *t);
    t->sorted   = NULL;
    t->unsorted = NULL;
    return t;
}

void pq_finalize(T *t)
{
    if (*t == NULL ||
        ((*t)->sorted == NULL && (*t)->unsorted == NULL)) {
        return ;
    }

    dellist(&(*t)->sorted);
    dellist(&(*t)->unsorted);
    free(*t);
    *t = NULL;
}

static void dellist(link_t *t)
{
    if (*t == NULL) {
        return ;
    }

    link_t tmp;

    while ((tmp = (*t)->next) != NULL) {
        (*t)->next = tmp->next;
        dellink(&tmp);
    }

    dellink(t);
    *t = NULL;
}

/* insert into the list unordered */
void pq_insert(T t, item_t item)
{
    t->unsorted = newlink(item, t->unsorted);
}

item_t pq_delmax(T t)
{
    assert(!pq_empty(t));
    sort(t);
    return del(t, t->sorted);
}

int pq_empty(T t)
{
    return t->sorted == NULL && t->unsorted == NULL;
}

static item_t del(T t, link_t target)
{
    link_t prev = NULL;
    link_t cur  = t->sorted;

    while (cur != NULL && cur != target) {
        prev = cur;
        cur  = cur->next;
    }

    item_t ret = target->item;

    if (prev == NULL) { /* the head */
        t->sorted = target->next;
    } else {
        prev->next = target->next;
    }

    return ret;
}

static void sort(T t)
{
    link_t a = t->unsorted;
    link_t next;

    while (a != NULL) {
        next = a->next;
        link_t prev = NULL;
        link_t cur  = t->sorted;

        while (cur != NULL && a->item <= cur->item) {
            prev = cur;
            cur  = cur->next;
        }

        a->next = cur;

        if (prev == NULL) { /* the current inserted is the biggest */
            t->sorted = a;
        } else {
            prev->next = a;
        }

        a = next;
    }

    t->unsorted = NULL;
}
