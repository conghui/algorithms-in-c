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
typedef item_t *RandomAccessIterator;
static void *alloc(size_t size);
static void make_heap(RandomAccessIterator first, RandomAccessIterator last);
static void fixdown(item_t *a, int k, int n);
static void sort_heap(RandomAccessIterator first, RandomAccessIterator last);
static void insertionsort(item_t *a, int l, int r);
static int partition(item_t *a, int l, int r);
static void swap(item_t *a, item_t *b);
static void sort(item_t *a, int l, int r);
inline static bool lt(item_t a, item_t b);
static InputIterator find(InputIterator first, InputIterator last, EqualityComparable value);
item_t newitem(key_t key, const char *str);
void delitem(item_t *t);
T st_init(size_t capacity);
void st_finalize(T *t);
void st_insert(T t, item_t item);
item_t st_search(T t, key_t k);
void quicksort(item_t *a, int l, int r);
void heapsort(item_t *a, int l, int r);
item_t st_select(T t, size_t k);
void st_sort(T t, UnaryFunction f);
UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f);
bool st_full(T t);
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
    t->content[t->size++] = item;
}

item_t st_search(T t, key_t k)
{
    size_t i = 0;

    for (; i < t->size; i++) {
        if (t->content[i]->key == k) {
            return t->content[i];
        }
    }

    return NULL;
}

void quicksort(item_t *a, int l, int r)
{
    if (r - l <= 5) {
        return insertionsort(a, l, r);
    }

    int i = partition(a, l, r);
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}

void heapsort(item_t *a, int l, int r)
{
    make_heap(a + l, a + r + 1);
    sort_heap(a + l, a + r + 1);
}

static void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    int n = last - first;
    int k;

    for (k = n / 2; k >= 1; k--) {
        fixdown(first - 1, k, n);
    }
}

static void fixdown(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;

    while ((j = k*2) <= n) {
        if (j < n && lt(a[j], a[j+1])) {
            j++;
        }

        if (!lt(v, a[j])) {
            break;
        }

        a[k] = a[j];
        k    = j;
    }

    a[k] = v;
}

static void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    int n = last - first;

    while (n > 1) {
        swap(first, first + n - 1);
        fixdown(first - 1, 1, --n);
    }
}

static void insertionsort(item_t *a, int l, int r)
{
    int i;

    for (i = l + 1; i <= r; i++) {
        int j    = i;
        item_t v = a[j];

        for (; j >= l + 1 && lt(v, a[j-1]); j--) {
            a[j] = a[j-1];
        }

        a[j] = v;
    }
}

static int partition(item_t *a, int l, int r)
{
    int i    = l - 1;
    int j    = r;
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j]) && j != l) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}

static void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

static void sort(item_t *a, int l, int r)
{
    /*quicksort(a, l, r);*/
    /*insertionsort(a, l, r);*/
    heapsort(a, l, r);
}

item_t st_select(T t, size_t k)
{
    assert(k < t->size);
    sort(t->content, 0, t->size - 1);
    return t->content[k];
}

void st_sort(T t, UnaryFunction f)
{
    sort(t->content, 0, t->size - 1);
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

inline static bool lt(item_t a, item_t b)
{
    return a->key < b->key;
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
