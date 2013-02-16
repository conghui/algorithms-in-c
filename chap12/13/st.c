#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>

#include "st.h"

#define T st_t

#define bitsword (CHAR_BIT * sizeof(int))

struct _T {
    key_t *data;
    size_t maxkey;
    size_t size;
};

static void *alloc(size_t size);
static size_t getword(key_t k);
static size_t mvbits(key_t k);
static size_t wordcnt(size_t bits);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T st_init(size_t max)
{
    T t = alloc(sizeof *t);
    t->maxkey = max + 1;
    t->data   = alloc(wordcnt(t->maxkey) * sizeof *t->data);
    t->size   = 0;
    memset(t->data, 0, wordcnt(t->maxkey) * sizeof *t->data);
    return t;
}

void st_finalize(T *t)
{
    free((*t)->data);
    free(*t);
    *t = NULL;
}

void st_insert(T t, key_t k)
{
    t->data[getword(k)] |= (1 << mvbits(k));
    t->size++;
}

void st_delete(T t, key_t k)
{
    t->data[getword(k)] &= ~(1 << mvbits(k));
    t->size--;
}

int st_select(T t, int k)
{
    size_t i;

    for (i = 0; i < t->maxkey; i++) {
        if ((t->data[getword(i)] & (1 << mvbits(k))) == 1)
            if (k-- == 0) {
                return i;
            }
    }

    return -1;
}

double st_avg(T t)
{
    double sum = 0.0;
    size_t i;

    for (i = 0; i < t->maxkey; i++) {
        if ((t->data[getword(i)] & (1 << mvbits(i))) != 0) {
            sum += i;
        }
    }

    return sum / t->size;
}

static size_t getword(key_t k)
{
    return k / bitsword;
}

static size_t mvbits(key_t k)
{
    return bitsword - (k % bitsword + 1);
}

static size_t wordcnt(size_t bits)
{
    return (bits / bitsword + 1);
}
