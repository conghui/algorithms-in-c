#include <stdio.h>
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

struct T {
    item_t *content;
    size_t size;
    size_t capacity;
};

typedef item_t EqualityComparable;
static void *alloc(size_t size);
inline static bool lt(key_t a, key_t b);
static InputIterator find(InputIterator first, InputIterator last, EqualityComparable value);
item_t newitem(key_t key, const char *str);
void delitem(item_t *t);
T st_init(size_t capacity);
void st_finalize(T *t);
void st_insert(T t, item_t item);
item_t st_search(T t, key_t k);
item_t st_select(T t, size_t k);
void st_sort(T t, UnaryFunction f);
UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f);
bool st_full(T t);
bool st_empty(T t);
key_t getkey(item_t v);
const char *getstr(item_t x);
void st_delete(T t, item_t x);

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
    free((*t)->str);
    free(*t);
    *t = NULL;
}

T st_init(size_t capacity)
{
    T t         = alloc(sizeof *t);
    t->capacity = capacity;
    t->size     = 0;
    t->content  = alloc(capacity * sizeof *t->content);
    return t;
}

void st_finalize(T *t)
{
    size_t i;

    for (i = 0; i < (*t)->size; i++) {
        delitem(&(*t)->content[i]);
    }

    free((*t)->content);
    free(*t);
    *t = NULL;
}

void st_insert(T t, item_t item)
{
    assert(!st_full(t));
    size_t i = t->size++;
    key_t v = item->key;

    for (; i > 0 && lt(v, t->content[i-1]->key); i--) {
        t->content[i] = t->content[i-1];
    }

    t->content[i] = item;
}

item_t st_search(T t, key_t k)
{
    size_t i = 0;

    for (; i < t->size && t->content[i]->key < k; i++) ;

    return t->content[i]->key == k ? t->content[i] : NULL;
}

item_t st_select(T t, size_t k)
{
    assert(k < t->size);
    return t->content[k];
}

void st_sort(T t, UnaryFunction f)
{
    for_each(t->content, t->content + t->size, f);
}

UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f)
{
    while (first != last) {
        f(*first++);
    }

    return f;
}


bool st_full(T t)
{
    return t->size == t->capacity;
}

bool st_empty(T t)
{
    return t->size == 0;
}

inline static bool lt(key_t a, key_t b)
{
    return a < b;
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
    item_t *xx = find(t->content, t->content + t->size, x);

    if (xx == t->content + t->size) {
        return ;
    }

    delitem(xx);
    size_t i = xx - t->content;

    for (; i < t->size - 1; i++) {
        t->content[i] = t->content[i+1];
    }

    t->size--;
}

size_t st_size(T t)
{
    return t->size;
}

static InputIterator find(
    InputIterator      first,
    InputIterator      last,
    EqualityComparable value)
{
    for (; first != last; ++first)
        if (*first == value) {
            break;
        }

    return first;
}

void st_searchinsert(T t, item_t item)
{
    item_t *xx = find(t->content, t->content + t->size, item);

    if (xx == t->content + t->size) { /* item not found */
        /* insert the item */
        st_insert(t, item);
    }
}
