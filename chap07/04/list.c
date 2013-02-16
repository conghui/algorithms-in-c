#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

#define T list_t
#define item_t int

struct node_t {
    item_t item;
    link_t next;
    link_t prev;
} ;

struct _T {
    link_t head;
    link_t tail;
};
static void *alloc(size_t size);
static link_t newlink(item_t item, link_t prev, link_t next);
static void dellink(link_t *t);
static void quick_sort(T t, link_t begin, link_t end);
static link_t partition(link_t begin, link_t end);
T list_init(size_t n);
void list_finalize(T *t);
void list_push_back(T t, item_t item);
void list_print(T t);
void list_sort(T t);
void swap(item_t *a, item_t *b);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(item_t item, link_t prev, link_t next)
{
    link_t t = alloc(sizeof *t);
    t->item  = item;
    t->prev  = prev;
    t->next  = next;
    return t;
}

static void dellink(link_t *t)
{
    free(*t);
    *t = NULL;
}

T list_init(size_t n)
{
    T t     = alloc(sizeof *t);
    t->head = NULL;
    t->tail = NULL;

    while (n-- > 0) {
        list_push_back(t, rand() % 100);
    }

    return t;
}

void list_finalize(T *t)
{
    link_t tmp;

    while ((tmp = (*t)->head)) {
        (*t)->head = tmp->next;
        dellink(&tmp);
    }

    free(*t);
    *t = NULL;
}

void list_push_back(T t, item_t item)
{
    if (t->head == NULL) { /* the list is empty */
        t->head = newlink(item, NULL, NULL);
        t->tail = t->head;
    } else {
        t->tail->next = newlink(item, t->tail, NULL);
        t->tail       = t->tail->next;
    }
}

void list_print(T t)
{
    link_t cur;

    for (cur = t->head; cur != NULL; cur = cur->next) {
        printf("%3d ", cur->item);
    }

    putchar('\n');
}

void list_sort(T t)
{
    quick_sort(t, t->head, t->tail);
}

static void quick_sort(T t, link_t begin, link_t end)
{
    if (begin == end || end == NULL || begin == NULL || begin->prev == end) {
        return;
    }

    link_t i = partition(begin, end);

    if (i) {
        quick_sort(t, begin, i->prev);
        quick_sort(t, i->next, end);
    }
}

/* begin and end are not null pointers */
static link_t partition(link_t begin, link_t end)
{
    link_t i = begin;
    link_t j = end->prev;
    item_t v = end->item;

    for (; ;) {
        while (i->item < v) {
            i = i->next;
        }

        while (j != begin && j->item > v) {
            j = j->prev;
        }

        if (i == j || i->prev == j) {
            break;
        }

        swap(&i->item, &j->item);
    }

    swap(&i->item, &end->item);
    return i;
}

void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

