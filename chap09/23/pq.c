#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "pq.h"

#define T pq_t
#define item_t int

struct _T {
    item_t *content;
    size_t capacity;
    size_t size;
};
static void *alloc(size_t size);
static int full(T t);
static void fixup(item_t *a, int k);
static void fixdown(item_t *a, int k, int n);
static void swap(item_t *a, item_t *b);
static int lt(item_t a, item_t b);
T pq_init(size_t n);
void pq_finalize(T *t);
void pq_insert(T t, item_t item);
item_t pq_delmax(T t);
int pq_empty(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T pq_init(size_t n)
{
    T t         = alloc(sizeof *t);
    t->content  = alloc((n+1) * sizeof *t->content);
    t->capacity = n;
    t->size     = 0;
    return t;
}

void pq_finalize(T *t)
{
    free((*t)->content);
    free(*t);
    *t = NULL;
}

void pq_insert(T t, item_t item)
{
    assert(!full(t));
    t->content[++t->size] = item;
    fixup(t->content, t->size);
}

static int full(T t)
{
    return t->size == t->capacity;
}

static void fixup(item_t *a, int k)
{
    /* insertion sort style */
    item_t v = a[k];

    for (; k > 1 && lt(a[k/2], v); k /= 2) {
        a[k] = a[k/2];
    }

    a[k] = v;
}

item_t pq_delmax(T t)
{
    /* remenber to change the a[1] instead of a[0],
     * because the the first element is inserted in position 1
     * instead of position 0*/
    swap(&t->content[1], t->content + t->size);
    fixdown(t->content, 1, t->size - 1);
    return t->content[t->size--];
}

int pq_empty(T t)
{
    return t->size == 0;
}

static void fixdown(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;

    /* remember to use sign <= instead of <, we should include
     * testing the last element*/
    while ((j = 2*k) <= n) {
        /* test if the a[k] node has two children,
         * if j == n, then a[k] has only one child, and a[j+1]
         * will out of bound, the test is important!! */
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

static void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

static int lt(item_t a, item_t b)
{
    return a < b;
}

void pq_print(T t)
{
    size_t i;

    for (i = 1; i <= t->size; i++) {
        printf("%3d ", t->content[i]);
    }

    printf("\n");
}
