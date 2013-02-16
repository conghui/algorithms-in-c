#include "heap3.h"

static void fixdown3(item_t *a, int k, int n);
inline static int parent3(int k);
inline static int lt(item_t a, item_t b);
inline static int max(item_t *a, int k, int n);
inline static int parent2(int k);
static void fixdown2(item_t *a, int k, int n);
static void heap_sort3(Iterator first, Iterator last);
inline static void swap(item_t *a, item_t *b);
static void sort_heap2(Iterator first, Iterator last);
void make_heap2(Iterator first, Iterator last);
void make_heap3(Iterator first, Iterator last);
void heapsort3(item_t *a, int l, int r);
void heapsort2(item_t *a, int l, int r);

static void fixdown3(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;

    /* we should include the most left one */
    while ((j = 3*k-1) <= n) {
        int m = max(a, k, n);

        if (!lt(v, a[m])) {
            break;
        }

        a[k] = a[m];
        k    = m;
    }

    a[k] = v;
}

inline static int parent3(int k)
{
    return (k+1)/3;
}

inline static int lt(item_t a, item_t b)
{
    compTimes++;
    return a < b;
}

inline static int max(item_t *a, int k, int n)
{
    int max = 3*k-1;
    int i;
    int j = 1;

    for (i = max+1; i <= n && j < 3; i++, j++) {
        if (lt(a[max], a[i])) {
            max = i;
        }
    }

    return max;
}

inline static int parent2(int k)
{
    return k / 2;
}

static void fixdown2(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;

    while ((j = 2*k) <= n) {
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


void make_heap2(Iterator first, Iterator last)
{
    int n = last - first;
    int k;

    for (k = parent2(n); k >= 1; k--) {
        fixdown2(first - 1, k, n);
    }
}

void make_heap3(Iterator first, Iterator last)
{
    int n = last - first;
    int k;

    for (k = (n+1) / 3; k >= 1; k--) {
        fixdown3(first - 1, k, n);
    }
}

void heapsort3(item_t *a, int l, int r)
{
    Iterator first = a + l;
    Iterator last  = a + r + 1;
    make_heap3(first, last);
    heap_sort3(first, last);
}

static void heap_sort3(Iterator first, Iterator last)
{
    int n = last - first;

    while (n > 1) {
        swap(first, first + n - 1);
        fixdown3(first - 1, 1, --n);
    }
}

inline static void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

void heapsort2(item_t *a, int l, int r)
{
    Iterator first = a + l;
    Iterator last  = a + r + 1;
    make_heap2(first, last);
    sort_heap2(first, last);
}

static void sort_heap2(Iterator first, Iterator last)
{
    int n = last - first;

    while (n > 1) {
        swap(first, first + n - 1);
        fixdown2(first - 1, 1, --n);
    }
}
