#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "st.h"

#define T st_t
#define MAXSIZE 10000000

struct _T {
    struct {
        key_t *data;
        size_t capacity;
        size_t size;
    } sorted, unsorted;
};
static void *alloc(size_t size);
inline static int eq(key_t a, key_t b);
static void print(key_t *a, int n);
static void quicksort(key_t *a, int l, int r);
static int partition(key_t *a, int l, int r);
inline static int lt(key_t a, key_t b);
inline static void swap(key_t *a, key_t *b);
static void merge(key_t *c, key_t *a, int N, key_t *b, int M);
inline static int le(key_t a, key_t b);
T st_init(size_t capacity);
void st_finalize(T *t);
size_t st_size(T t);
bool st_search(T t, key_t k);
bool binary_search(key_t *a, int l, int r, key_t value);
void st_insert(T t, key_t k);
void st_sort(T t);

static void *
alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T
st_init(size_t capacity)
{
    T t                  = alloc(sizeof *t);
    t->sorted.data       = alloc(capacity * sizeof *t->sorted.data);
    t->sorted.capacity   = capacity;
    t->sorted.size       = 0;
    t->unsorted.data     = alloc(capacity * sizeof *t->unsorted.data);
    t->unsorted.capacity = capacity;
    t->unsorted.size     = 0;
    return t;
}

void
st_finalize(T *t)
{
    free((*t)->sorted.data);
    free((*t)->unsorted.data);
    free(*t);
    *t = NULL;
}

size_t
st_size(T t)
{
    return t->sorted.size + t->unsorted.size;
}

bool
st_search(T t, key_t k)
{
    st_sort(t);
    return binary_search(t->sorted.data, 0, t->sorted.size - 1, k);
}

bool binary_search(key_t *a, int l, int r, key_t value)
{
    if (r < l) {
        return false;
    }

    int mid = l + ((r-l) >> 1);

    if (eq(value, a[mid])) {
        return true;
    }

    if (lt(value, a[mid])) {
        return binary_search(a, l, mid - 1, value);
    }

    return binary_search(a, mid + 1, r, value);
}

void
st_insert(T t, key_t k)
{
    t->unsorted.data[t->unsorted.size++] = k;
}

inline static int
eq(key_t a, key_t b)
{
    return !lt(a, b) && !lt(b, a);
}

void st_sort(T t)
{
    if (t->unsorted.size == 0) {
        return;
    }

    quicksort(t->unsorted.data, 0, t->unsorted.size - 1);
    merge(t->sorted.data, t->sorted.data, t->sorted.size,
          t->unsorted.data, t->unsorted.size);
    t->sorted.size  += t->unsorted.size;
    t->unsorted.size = 0;
}

static void
print(key_t *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%3d ", a[i]);
    }

    printf("\n");
}

static void
quicksort(key_t *a, int l, int r)
{
    if (r <= l) {
        return;
    }

    int i = partition(a, l, r);
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}

static int
partition(key_t *a, int l, int r)
{
    int i   = l - 1;
    int j   = r;
    key_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j])) if (j == l) {
                break;
            }

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}

inline static int
lt(key_t a, key_t b)
{
    return a < b;
}

inline static void
swap(key_t *a, key_t *b)
{
    key_t tmp = *a;
    *a        = *b;
    *b        = tmp;
}


static void
merge(key_t *c, key_t *a, int M, key_t *b, int N)
{
    static key_t aux[MAXSIZE];
    int i = 0;
    int j = 0;
    int k = 0;

    for (; k < M + N; k++) {
        if (i == M) {
            aux[k] = b[j++];
            continue;
        }

        if (j == N) {
            aux[k] = a[i++];
            continue;
        }

        aux[k] = le(a[i], b[j]) ? a[i++] : b[j++];
    }

    memcpy(c, aux, (M+N)*sizeof *c);
}

inline static int
le(key_t a, key_t b)
{
    return lt(a, b) || (!lt(a, b) && !lt(b, a));
}
