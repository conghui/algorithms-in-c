#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "st.h"

#define T st_t

struct item_t {
    key_t key;
    char *str;
};

typedef struct node_t *link_t;

struct node_t {
    item_t item;
    link_t next;
};

struct T {
    link_t head;
    link_t tail;
    size_t size;
};

typedef item_t EqualityComparable;
static void *alloc(size_t size);
static link_t newlink(item_t item, link_t next);
static void dellink(link_t t);
inline static int lt(item_t a, item_t b);
static int le(item_t a, item_t b);
item_t newitem(key_t key, const char *str);
void delitem(item_t t);
T st_init(size_t capacity);
void st_finalize(T t);
void st_insert(T t, item_t item);
item_t st_search(T t, key_t k);
item_t st_select(T t, size_t k);
void st_sort(T t, UnaryFunction f);
UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f);
bool st_empty(T t);
key_t getkey(item_t v);
const char *getstr(item_t x);
void st_delete(T t, item_t x);
size_t st_size(T t);
void st_searchinsert(T t, item_t item);
void st_join(T t1, T t2);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

item_t newitem(key_t key, const char *str)
{
    item_t t = alloc(sizeof *t);
    t->key    = key;
    t->str    = alloc(strlen(str) + 1);
    strcpy(t->str, str);
    return t;
}

void delitem(item_t t)
{
    if (t == NULL) {
        return ;
    }

    free(t->str);
    free(t);
}

static link_t newlink(item_t item, link_t next)
{
    link_t t = alloc(sizeof *t);
    t->item  = item;
    t->next  = next;
    return t;
}

static void dellink(link_t t)
{
    if (t == NULL) {
        return ;
    }

    delitem(t->item);
    free(t);
}

T st_init(size_t capacity)
{
    (void)capacity;
    T t         = alloc(sizeof *t);
    t->size     = 0;
    t->head = newlink(newitem(INT_MIN, "head"), NULL);
    t->tail = newlink(newitem(INT_MIN, "head"), NULL);
    t->head->next = t->tail;
    return t;
}

void st_finalize(T t)
{
    if (t == NULL) {
        return ;
    }

    link_t tmp;

    while ((tmp = t->head->next) != t->tail) {
        t->head->next = tmp->next;
        dellink(tmp);
    }

    /* delete the head and the tail */
    dellink((t)->head);
    dellink((t)->tail);
    /* delete the link list  */
    free(t);
}

/* it is an ordered list, the insert operator takes O(n)  */
void st_insert(T t, item_t item)
{
    link_t prev = t->head;
    link_t cur  = prev->next;

    for (; cur != t->tail && lt(cur->item, item); prev = cur, cur = cur->next) ;

    prev->next = newlink(item, cur);
    t->size++;
}

inline static int lt(item_t a, item_t b)
{
    return a->key < b->key;
}

item_t st_search(T t, key_t k)
{
    link_t cur = t->head->next;

    for (; cur != t->tail && k < cur->item->key; cur = cur->next) ;

    return cur->item->key == k ? cur->item : NULL;
}

item_t st_select(T t, size_t k)
{
    link_t cur = t->head->next;

    for (; k-- > 0 && cur != t->tail; cur = cur->next) ;

    return cur->item;
}


void st_sort(T t, UnaryFunction f)
{
    link_t cur = t->head->next;

    for (; cur != t->tail; cur = cur->next) {
        f(cur->item);
    }
}

UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f)
{
    while (first != last) {
        f(*first++);
    }

    return f;
}


bool st_empty(T t)
{
    return t->head->next == t->tail;
}

key_t getkey(item_t v)
{
    return v->key;
}

const char *getstr(item_t x)
{
    return x->str;
}

void st_delete(T t, item_t x)
{
    link_t prev = t->head;
    link_t cur  = prev->next;

    for (; cur != t->tail; prev = cur, cur = cur->next) {
        if (cur->item == x) {
            prev->next = cur->next;
            dellink(cur);
            t->size--;
            break;
        }
    }
}

size_t st_size(T t)
{
    return t->size;
}

void st_searchinsert(T t, item_t item)
{
    if (st_search(t, getkey(item)) == NULL) {
        st_insert(t, item);
    }
}

/* join two list t1 and t2. t2 is merged into t1 and will be deleted in the
 * function. t1 and t2 are the list in sorted order, so we can merge the two
 * list using merge sort */
void st_join(T t1, T t2)
{
    link_t a = t1->head->next;
    link_t b = t2->head->next;
    link_t c = t1->head;

    while (a != t1->tail && b != t2->tail) {
        if (le(a->item, b->item)) {
            c = c->next = a;
            a = a->next;
        } else {
            c = c->next = b;
            b = b->next;
        }
    }

    if (a != t1->tail) {
        c->next = a;
        t2->head->next = t2->tail;
    } else if (b != t2->tail) {
        c->next = b;
        link_t tmp = t1->tail;
        t1->tail = t2->tail;
        t2->tail       = tmp;
        t2->head->next = t2->tail;
    }

    t2->size = 0;
}

static int le(item_t a, item_t b)
{
    return !lt(a, b) && !lt(b, a);
}
