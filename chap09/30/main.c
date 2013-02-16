#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "type.h"
#include "glovar.h"
#include "heap3.h"

#define MAX 100

static size_t heapsort(item_t *a, int l, int r);
static size_t fixdown(item_t *a, int k, int n);
static void swap(item_t *a, item_t *b);
static int lt(item_t a, item_t b);
static void for_each(item_t *first, item_t *last, fnc_t f);
static void init(item_t *x);
static int comp(const void *l, const void *r);
void test2();
void print(item_t *x);
void test1();

int main(void)
{
    test2();
    return 0;
}

void test2()
{
    int k = 1000000;
    int n = 1000;
    printf("%10s%15s%15s\n", "n", "2-tree", "3-tree");

    for (; n <= k; n *= 10) {
        item_t *a = malloc(n * sizeof *a);
        item_t *b = malloc(n * sizeof *b);
        for_each(a, a + n, init);
        memcpy(b, a, n * sizeof *b);
        heapsort2(b, 0, n - 1);
        size_t cnt2 = compTimes;
        compTimes   = 0;
        heapsort3(a, 0, n - 1);
        size_t cnt3 = compTimes;

        if (memcmp(a, b, n * sizeof *a) == 0) {
            printf("%10d%15u%15u\n", n, cnt2, cnt3);
        } else {
            printf("No\n");
        }

        free(a);
        free(b);
    }
}

void print(item_t *x)
{
    printf("%3d", *x);
}

void test1()
{
    int n     = 1000;
    int i;

    for (i = 0; i < 4; i++, n *= 10) {
        size_t cmpcnt;
        item_t *a = malloc(n * sizeof *a);
        item_t *b = malloc(n * sizeof *b);
        for_each(a, a + n, init);
        memcpy(b, a, n * sizeof *b);
        cmpcnt = heapsort(a, 0, n - 1);
        qsort(b, n, sizeof *b, comp);

        if (memcmp(a, b, n * sizeof *a) == 0) {
            printf("for n = %d, cmpcnt / n = %f\n",
                   n, (double)cmpcnt / n);
        } else {
            printf("No\n");
        }

        free(a);
        free(b);
    }
}

static size_t heapsort(item_t *a, int l, int r)
{
    int n = r - l + 1;
    int k;
    size_t cmpcnt = 0;

    /* construct a heap */
    for (k = n / 2; k >= 1; k--) {
        cmpcnt += fixdown(&a[l-1], k, n);
    }

    /* sort the heap */
    while (n > 0) {
        swap(a, &a[n-1]);
        cmpcnt += fixdown(&a[l-1], 1, --n);
    }

    return cmpcnt;
}

static size_t fixdown(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;
    size_t cmpcnt = 0;

    while ((j = 2 * k) <= n) {
        cmpcnt += 2;

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
    return cmpcnt;
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
