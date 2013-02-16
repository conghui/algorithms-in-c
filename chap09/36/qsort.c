#include <stdio.h>

#include "qsort.h"
static void _qselect(item_t *a, int l, int r, int k);
void quick_sort(item_t *a, int l, int r);
int partition(item_t *a, int l, int r);
void qselect(item_t *a, int n, int k);

void quick_sort(item_t *a, int l, int r)
{
    if (r <= l) {
        return ;
    }

    int i = partition(a, l, r);
    quick_sort(a, l, i - 1);
    quick_sort(a, i + 1, r);
}

int partition(item_t *a, int l, int r)
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

void qselect(item_t *a, int n, int k)
{
    compcnt = 0;
    _qselect(a, 0, n - 1, k - 1);
    printf("The %dth smallest element is %u, the "
           "quicksort style use %u comparition\n",
           k, a[k-1], compcnt);
}

static void _qselect(item_t *a, int l, int r, int k)
{
    if (r <= l) {
        return;
    }

    int i = partition(a, l, r);

    if (i < k) {
        _qselect(a, i + 1, r, k);
    } else { /* i > k */
        _qselect(a, l, i - 1, k);
    }
}
