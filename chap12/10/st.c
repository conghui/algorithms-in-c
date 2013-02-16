#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "st.h"

#define T st_t

struct _item {
    key_t key;
    char *str;
};

struct _T {
    item_t *content;
    key_t  maxkey;
    size_t size;
};


static void *alloc(size_t size);
static ptrdiff_t count_if(InputIterator first, InputIterator last, Predicate pred);
static bool hasElement(item_t x);
static UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f);
static key_t key(const item_t x);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T st_init(key_t maxkey)
{
    T t       = alloc(sizeof *t);
    t->maxkey = maxkey + 1;
    t->size = 0;
    memset(t->content, 0, t->maxkey * sizeof *t->content);
    return t;
}

void st_finalize(T *_t)
{
    int i;
    T t = *_t;

    for (i = 0; i < t->maxkey; i++) {
        if (t->content[i]) {
            free(t->content[i]);
        }
    }

    free(t);
    *_t = NULL;
}

int st_count(T t)
{
    return t->size;
}

static ptrdiff_t count_if(
    InputIterator first,
    InputIterator last,
    Predicate     pred)
{
    ptrdiff_t cnt = 0;

    while (first != last) if (pred(*first++)) {
            cnt++;
        }

    return cnt;
}

static bool hasElement(item_t x)
{
    return x != NULL;
}

void st_insert(T t, item_t x)
{
    t->content[key(x)] = x;
    t->size++;
}

item_t st_search(T t, key_t key)
{
    return t->content[key];
}

void st_delete(T t, item_t item)
{
    item_t tmp = t->content[key(item)];
    t->content[key(item)] = NULL;
    t->size--;
    free(tmp);
}

item_t st_select(T t, int k)
{
    int i;

    for (i = 0; i < t->maxkey; i++) {
        if (t->content[i])
            if (k-- == 0) {
                return t->content[i];
            }
    }

    return NULL;
}

void st_sort(T t, UnaryFunction f)
{
    for_each(t->content, t->content + t->maxkey, f);
}

static UnaryFunction for_each(
    InputIterator first,
    InputIterator last,
    UnaryFunction f)
{
    while (first != last) {
        f(*first++);
    }

    return f;
}

static key_t key(const item_t x)
{
    return x->key;
}
