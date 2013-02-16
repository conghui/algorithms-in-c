#ifndef QSORT_H

#define QSORT_H

#include "glovar.h"
#include "type.h"
#include "util.h"

void quick_sort(item_t *a, int l, int r);
int partition(item_t *a, int l, int r);
void qselect(item_t *a, int n, int k);

#endif /* end of include guard: QSORT_H */
