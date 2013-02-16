#ifndef UTIL_H

#define UTIL_H

#include <stdlib.h>

#include "type.h"
#include "glovar.h"

void *alloc(size_t size);
void print(item_t *x);
item_t randNum();
void for_each(Iterator first, Iterator last, Function f);
void generate(Iterator first, Iterator last, Generator gen);
void selection(item_t *a, int n, int k);
int comp(const void *l, const void *r);
void swap(item_t *a, item_t *b);
int lt(item_t a, item_t b);
int gt(item_t a, item_t b);

#endif /* end of include guard: UTIL_H */
