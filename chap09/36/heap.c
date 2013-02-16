#include <stdio.h>
#include "util.h"
#include "heap.h"

static void fixup(item_t *a, int k, Compare comp);
static void fixdown(item_t *a, int k, int n, Compare comp);

static void fixup(item_t *a, int k, Compare comp)
{
    item_t v = a[k];

    for (; k > 1 && comp(a[k/2], v); k /= 2) {
        a[k] = a[k/2];
    }

    a[k] = v;
}

static void fixdown(item_t *a, int k, int n, Compare comp)
{
    item_t v = a[k];
    int j;

    while ((j = 2 *k) <= n) {
        if (j < n && comp(a[j], a[j+1])) {
            j++;
        }

        if (!comp(v, a[j])) {
            break;
        }

        a[k] = a[j];
        k    = j;
    }

    a[k] = v;
}


void make_heap(Iterator first, Iterator last, Compare comp)
{
    int n = last - first;
    int k;

    for (k = n / 2; k >= 1; k--) {
        fixdown(first - 1, k, n, comp);
    }
}

void push_heap(Iterator first, Iterator last, Compare comp)
{
    int k = last - first;
    fixup(first - 1, k,comp);
}

void pop_heap(Iterator first, Iterator last, Compare comp)
{
    int n = last - first;
    swap(first, last - 1);
    fixdown(first - 1, 1, n-1, comp);
}

void hselect(item_t *a, int n, int k, Compare comp)
{
    compcnt = 0;
    make_heap(a, a + n, comp);
    int i;

    for (i = 1; i < k; i++) {
        pop_heap(a, a + n - i + 1, comp);
    }

    printf("The %dth smallest element is %u, the "
           "heapsort  style use %u comparition\n",
           k, *a, compcnt);
}
