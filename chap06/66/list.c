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

/* bubble sort */
void list_sort(T t)
{
    link_t out = NULL;

    if (t->head == NULL || t->head->next == NULL) {
        return ; /* no need to sort */
    }

    while (t->head->next != NULL) {/* at least two node  */
        link_t one, two, three;
        one   = NULL;
        two   = t->head;
        three = two->next;

        while (three != NULL) {
            if (two->item > three->item) {
                two->next   = three->next;
                three->next = two;

                if (one == NULL) { /* two and three are the first two node */
                    t->head = three;
                    one     = t->head;
                } else {
                    one->next = three;
                }

                one   = three;
                two   = one->next;
                three = two->next;
            } else {
                one   = two;
                two   = one->next;
                three = two->next;
            }
        }

        /* two points to the last node, remove two from the list and insert it
         * into the new list: out */
        two->next = out;
        out       = two;
        one->next = NULL;
    }

    /* only one node */
    t->head->next = out;
    out           = t->head;
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
