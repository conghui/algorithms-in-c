#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "list.h"

#define T list_t
#define item_t int

struct node {
    item_t item;
    link_t next;
};

struct _T {
    link_t head;
    link_t tail;
};
static void *alloc(size_t size);
static link_t newlink(item_t item, link_t next);
static void dellink(link_t *t);
static link_t merge(link_t a, link_t b);
static link_t mergesort(link_t c);

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

    while ((tmp = (*t)->head) != NULL) {
        (*t)->head = tmp->next;
        dellink(&tmp);
    }

    free(*t);
    *t = NULL;
}

void list_pushback(T t, item_t item)
{
    if (t->head == NULL) { /* the list is empty */
        t->tail = t->head = newlink(item, NULL);
    } else {
        t->tail = t->tail->next = newlink(item, NULL);
    }
}

/* merge the two link a and b. return the sorted link */
static link_t merge(link_t a, link_t b)
{
    struct node t; /* declare it in order to use the next pointer */
    link_t c = &t; /* the sorted link */

    while (a != NULL && b != NULL) {
        if (a->item <= b->item) {
            c = c->next = a;
            a   = a->next;
        } else {
            c = c->next = b;
            b = b->next;
        }
    }

    /* append the remaining link to c */
    c->next = a == NULL ? b : a;
    return t.next; /* the head of the sorted list */
}

static link_t mergesort(link_t c)
{
    if (c == NULL || c->next == NULL) {
        return c;
    }

    link_t a = c; /* a points to the first half of the list */
    link_t b = c->next; /* b points to second half of the list */

    while (b != NULL && b->next != NULL) {
        c = c->next;
        b = b->next->next;
    }

    b       = c->next;
    c->next = NULL;
    return merge(mergesort(a), mergesort(b));
}

void list_sort(T t)
{
    t->head = mergesort(t->head);
    /* find the tail and reset it */
    link_t tmp;

    if ((tmp = t->head) == NULL) {
        t->tail = NULL;
        return ;
    }

    for (tmp = t->head; tmp->next != NULL; tmp = tmp->next) ;

    t->tail = tmp;
}

void list_print(T t)
{
    link_t tmp;

    for (tmp = t->head; tmp != NULL; tmp = tmp->next) {
        printf("%3d", tmp->item);
    }

    printf("\n");
}
