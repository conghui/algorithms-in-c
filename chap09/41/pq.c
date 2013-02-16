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
    item_t key;
    link_t prev;
    link_t next;
};

struct _T {
    link_t head;
    link_t tail;
};
static void *alloc(size_t size);
static link_t newlink(item_t key, link_t prev, link_t next);
static void dellink(link_t *t);
static link_t findmax(T t);
static item_t pq_dellink(link_t x);
static link_t find(T t, item_t key);
inline static int lt(item_t a, item_t b);
inline static int eq(item_t a, item_t b);
inline static void swaplink(link_t *a, link_t *b);
T pq_init();
void pq_finalize(T *_t);
int pq_empty(T t);
void pq_insert(T t, item_t item);
item_t pq_delete(T t, item_t key);
item_t pq_delmax(T t);
void pq_print(T t);
T pq_join(T t1, T t2);
T pq_copy(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(item_t key, link_t prev, link_t next)
{
    link_t t = alloc(sizeof *t);
    t->key   = key;
    t->prev  = prev;
    t->next  = next;
    return t;
}

static void dellink(link_t *t)
{
    free(*t);
    *t = NULL;
}

T pq_init()
{
    T t           = alloc(sizeof *t);
    t->head       = alloc(sizeof *t->head);
    t->tail       = alloc(sizeof *t->tail);
    t->head->next = t->tail;
    t->head->prev = t->tail;
    t->tail->next = t->head;
    t->tail->prev = t->head;
    return t;
}

void pq_finalize(T *_t)
{
    T t = *_t;
    assert(t);
    link_t tmp;

    while ((tmp = t->head->next) != t->tail) {
        t->head->next = tmp->next;
        dellink(&tmp);
    }

    /* all are deleted except the head and tail */
    dellink(&t->head);
    dellink(&t->tail);
    free(*_t);
    *_t = NULL;
}

int pq_empty(T t)
{
    return t->head->next == t->tail;
}

/* insert the element in descending order */
void pq_insert(T t, item_t item)
{
    link_t prev = t->head;
    link_t cur  = prev->next;

    for (; cur != t->tail; prev = cur, cur = cur->next) {
        if (!lt(item, cur->key)) {
            break;
        }
    }

    link_t nl  = newlink(item, prev, cur);
    prev->next = nl;
    cur->prev  = nl;
}

item_t pq_delete(T t, item_t key)
{
    /* find the link that contains the key */
    link_t todel = find(t, key);
    return pq_dellink(todel);
}

item_t pq_delmax(T t)
{
    assert(!pq_empty(t));
    /* find the maximum link */
    link_t maxlink = findmax(t);
    item_t retval  = maxlink->key;
    pq_dellink(maxlink);
    return retval;
}

static link_t findmax(T t)
{
    assert(!pq_empty(t));
    return t->head->next;
}

static item_t pq_dellink(link_t x)
{
    item_t ret = x->key;
    x->next->prev = x->prev;
    x->prev->next = x->next;
    dellink(&x);
    return ret;
}

static link_t find(T t, item_t key)
{
    link_t cur = t->head->next;

    for (; cur != t->tail; cur = cur->next) {
        if (eq(cur->key, key)) {
            return cur;
        }
    }

    return t->tail;
}


inline static int lt(item_t a, item_t b)
{
    return a < b;
}

inline static int eq(item_t a, item_t b)
{
    return !lt(a, b) && !lt(b, a);
}

void pq_print(T t)
{
    link_t cur;

    for (cur = t->head->next; cur != t->tail; cur = cur->next) {
        printf("%3d ", cur->key);
    }

    printf("\n");
}

T pq_join(T t1, T t2)
{
    /* connect the data of t1 and t2 */
    t1->tail->prev->next = t2->head->next;
    t2->head->next->prev = t1->tail->prev;
    /* connect the tail and head */
    t1->head->prev = t2->tail;
    t2->tail->next = t1->head;
    /* swap t1->tail and t2->tail */
    swaplink(&t1->tail, &t2->tail);
    /* fix t2 */
    t2->head->next = t2->tail;
    t2->head->prev = t2->tail;
    t2->tail->next = t2->head;
    t2->tail->prev = t2->head;
    pq_finalize(&t2);
    return t1;
}

inline static void swaplink(link_t *a, link_t *b)
{
    link_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

T pq_copy(T t)
{
    T c        = pq_init();
    link_t cur = t->tail->prev;

    for (; cur != t->head; cur = cur->prev) {
        pq_insert(c, cur->key);
    }

    return c;
}
