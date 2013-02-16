#ifndef HEAP_H

#define HEAP_H

#include "type.h"

void make_heap(Iterator first, Iterator last, Compare comp);
void push_heap(Iterator first, Iterator last, Compare comp);
void pop_heap(Iterator first, Iterator last, Compare comp);
void hselect(item_t *a, int n, int k, Compare comp);
#endif /* end of include guard: HEAP_H */
