#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "list.h"

#define T      list_t
#define item_t int

struct node_t {
    item_t item;
    link_t next;
};

struct _T {
    link_t head;
    link_t tail;
};

static void *alloc(size_t size);
static void settail(T t);
static link_t findmaxprev(link_t head);
link_t newlink(item_t item, link_t next);
void dellink(link_t *l);
T list_init();
void list_finalize(T *t);
void list_show(T t);
void list_sort(T t);
void list_append(T t, item_t item);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

link_t newlink(item_t item, link_t next)
{
    link_t nl = alloc(sizeof *nl);
    nl->item  = item;
    nl->next  = next;
    return nl;
}

void dellink(link_t *l)
{
    free(*l);
    *l = NULL;
}

T list_init()
{
    T t     = alloc(sizeof *t);
    t->head = NULL;
    t->tail = NULL;
    return t;
}

void list_finalize(T *t)
{
    link_t tmp;

    if (*t == NULL) {
        return ;
    }

    while ((tmp = (*t)->head) != NULL) {
        (*t)->head = tmp->next;
        dellink(&tmp);
    }

    free(*t);
    *t = NULL;
}

void list_show(T t)
{
    for (link_t cur = t->head; cur != NULL; cur = cur->next) {
        printf("%3d ", cur->item);
    }

    putchar('\n');
}

/* bubble sort */
void list_sort(T t)
{
    link_t out;
    link_t cur;

    if (t->head == NULL) {
        return ;
    }

    out = t->head;
    cur = t->head->next;
    out->next = NULL;

    while (cur != NULL) {
        link_t sort_prev = NULL; /* the prev in the sorted list */
        link_t sort_cur  = out;  /* the cur in the sorted list */
        link_t next = cur->next;

        while (sort_cur != NULL && sort_cur->item <= cur->item) {
            sort_prev = sort_cur;
            sort_cur  = sort_cur->next;
        }

        if (sort_prev == NULL) {
            out = cur;
        } else {
            sort_prev->next = cur;
        }

        cur->next       = sort_cur;
        cur = next;
    }

    t->head = out;
    settail(t);
}

static void settail(T t)
{
    link_t cur;

    for (cur = t->head; cur->next != NULL; cur = cur->next) ;

    t->tail = cur;
}

static link_t findmaxprev(link_t head)
{
    assert(head != NULL);

    if (head->next == NULL) { /* only one item */
        return NULL;
    }

    item_t max     = head->item;
    link_t prev    = head;
    link_t cur     = head->next;
    link_t maxprev = NULL;

    for (; cur != NULL; prev = cur, cur = cur->next) {
        if (max < cur->item) {
            max     = cur->item;
            maxprev = prev;
        }
    }

    return maxprev;
}

void list_append(T t, item_t item)
{
    link_t nl     = newlink(item, NULL);

    if (t->head == NULL && t->tail == NULL) {
        t->head = nl;
        t->tail = nl;
    } else {
        t->tail->next = nl;
        t->tail = nl;
    }
}
