#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX RAND_MAX

typedef int item_t;
typedef void (*fnc_t)(item_t *);

static size_t cmpcnt;

static void heapsort_floyd(item_t *a, int l, int r);
static void heapsort(item_t *a, int l, int r);
static void fixdown(item_t *a, int k, int n);
static void swap(item_t *a, item_t *b);
static void fixup(item_t *a, int k);
static int lt(item_t a, item_t b);
static void for_each(item_t *first, item_t *last, fnc_t f);
static void init(item_t *x);
static int comp(const void *l, const void *r);
void fixdown_floyd(item_t *a, int k, int n);

int main(void)
{
    int n     = 1000;
    int i;
    printf("%10s%15s%15s\n", "n", "heap/qsort", "floyd/qsort");

    for (i = 0; i < 4; i++, n *= 10) {
        item_t *a = malloc(n * sizeof *a);
        item_t *b = malloc(n * sizeof *b);
        item_t *c = malloc(n * sizeof *c);
        for_each(a, a + n, init);
        memcpy(b, a, n * sizeof *b);
        memcpy(c, a, n * sizeof *c);
        heapsort(a, 0, n - 1);
        qsort(b, n, sizeof *b, comp);

        if (memcmp(a, b, n * sizeof *a) == 0) {
            printf("%10d%15f", n, (double)cmpcnt/n);
        }

        cmpcnt = 0;
        heapsort_floyd(c, 0, n-1);

        if (memcmp(c, b, n * sizeof *b) == 0) {
            printf("%15f\n", (double)cmpcnt/n);
        }

        free(a);
        free(b);
        free(c);
    }

    return 0;
}

static void heapsort_floyd(item_t *a, int l, int r)
{
    int n = r - l + 1;
    int k;

    for (k = n / 2; k >= 1; k--) {
        fixdown(&a[l-1], k, n);
    }

    while (n > 1) {
        swap(a, &a[n-1]);
        fixdown_floyd(&a[l-1], l + 1, --n);
    }
}

static void heapsort(item_t *a, int l, int r)
{
    int n = r - l + 1;
    int k;

    /* construct a heap */
    for (k = n / 2; k >= 1; k--) {
        fixdown(&a[l-1], k, n);
    }

    /* sort the heap */
    while (n > 0) {
        swap(a, &a[n-1]);
        fixdown(&a[l-1], 1, --n);
    }
}

static void fixdown(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;

    while ((j = 2 * k) <= n) {
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

void fixdown_floyd(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;

    while ((j = 2 * k) <= n) {
        if (j < n && lt(a[j], a[j+1])) {
            j++;
        }

        /*if (!lt(v, a[j])) break;*/
        a[k] = a[j];
        k    = j;
    }

    a[k] = v;
    fixup(a, k);
}

static void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

static void fixup(item_t *a, int k)
{
    item_t v = a[k];

    for (; k > 1 && lt(a[k/2], v); k /= 2) {
        a[k] = a[k/2];
    }

    a[k] = v;
}

static int lt(item_t a, item_t b)
{
    cmpcnt++;
    return a < b;
}

static void for_each(item_t *first, item_t *last, fnc_t f)
{
    for (; first != last; ++first) {
        f(first);
    }
}

static void init(item_t *x)
{
    *x = rand() % MAX;
}

static int comp(const void *l, const void *r)
{
    return *(item_t *)l - *(item_t *)r;
}
