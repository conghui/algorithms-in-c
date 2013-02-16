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
static link_t findmaxprev(link_t head);

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

void list_sort(T t)
{
    /* selection sort */
    link_t out = NULL;
    int settail = 0;

    while (t->head != NULL) {
        link_t max_prev; /* the prev node of max node */
        link_t max;     /* max node */
        max_prev       = findmaxprev(t->head);

        if (max_prev == NULL) { /* max node is the first node */
            max     = t->head;
            t->head = max->next;
        } else {
            max            = max_prev->next;
            max_prev->next = max->next;
        }

        max->next      = out;
        out            = max;

        if (!settail) {
            t->tail = out;
            settail = 1;
        }
    }

    t->head = out;
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
