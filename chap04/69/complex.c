#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "complex.h"

#define T complex_t

struct T {
    double real;
    double image;
};
static void *alloc(size_t size);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T complex_init(double r, double i)
{
    T t      = alloc(sizeof * t);
    t->real  = r;
    t->image = i;
    return t;
}

void complex_finalize(T *t)
{
    free(*t);
    *t = NULL;
}

double complex_real(T t)
{
    return t->real;
}

double complex_image(T t)
{
    return t->image;
}

T complex_add(T a, T b)
{
    double r = a->real + b->real;
    double i = a->image + b->image;
    return complex_init(r, i);
}

T complex_mult(T a, T b)
{
    double r = a->real * b->real - a->image * b->image;
    double i = a->real * b->image + a->image * b->real;
    return complex_init(r, i);
}

T complex_copy(T t)
{
    return complex_init(t->real, t->image);
}

void complex_print(T t)
{
    printf("%g+%gi", t->real, t->image);
}
