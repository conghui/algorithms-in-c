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
bool st_full(T t);
static void *alloc(size_t size);
static link_t newlink(item_t item, link_t next);
static void dellink(link_t *t);
inline static int lt(item_t a, item_t b);
static void _sort(T t);
item_t newitem(key_t key, const char *str);
void delitem(item_t *t);
T st_init(size_t capacity);
void st_finalize(T *t);
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

void delitem(item_t *t)
{
    if (*t == NULL) {
        return ;
    }

    free((*t)->str);
    free(*t);
    *t = NULL;
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
    if (*t == NULL) {
        return ;
    }

    delitem(&(*t)->item);
    free(*t);
    *t = NULL;
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

void st_finalize(T *t)
{
    if (*t == NULL) {
        return ;
    }

    link_t tmp;

    while ((tmp = (*t)->head->next) != (*t)->tail) {
        (*t)->head->next = tmp->next;
        dellink(&tmp);
    }

    /* delete the head and the tail */
    dellink(&(*t)->head);
    dellink(&(*t)->tail);
    /* delete the link list  */
    free(*t);
    *t = NULL;
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

static void _sort(T t)
{
    if (t == NULL || t->head->next == t->tail) {
        return ;
    }

    link_t x = t->head->next;
    link_t next;
    t->head->next = t->tail;

    for (; x != t->tail; x = next) {
        next        = x->next;
        link_t prev = t->head;
        link_t cur  = prev->next;

        for (; cur != t->tail && x->item->key > cur->item->key;
             prev = cur, cur = cur->next) ;

        x->next = cur;
        prev->next = x;
    }
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
    return t->size == 0;
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
            dellink(&cur);
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
