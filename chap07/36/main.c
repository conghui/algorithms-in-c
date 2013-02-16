#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 1000000

typedef int item_t;

static int lt(item_t a, item_t b);
static void swap(item_t *a, item_t *b);
static int partition(item_t *a, int l, int r);
static int partition2(item_t *a, int l, int r);
void quick_sort1(item_t *a, int l, int r);
void quick_sort2(item_t *a, int l, int r);
int le(item_t a, item_t b);
void insertion_sort(item_t *a, int l, int r);
int comp(const void *l, const void *r);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void print(item_t *x);
void init(item_t *x);

int main(void)
{
    int n     = 100000;
    item_t *a = (item_t *)malloc(n * sizeof *a);
    for_each(a, a + n, init);
    /*for_each(a, a + n, print);    putchar('\n'); putchar('\n');*/
    clock_t begin = clock();
    quick_sort1(a, 0, n-1);
    /*quick_sort2(a, 0, n-1);*/
    /*insertion_sort(a, 0, n-1);*/
    /*qsort(a, n, sizeof *a, comp);*/
    clock_t end = clock();
    for_each(a, a + n, print);
    putchar('\n');
    printf("time elapse: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);
    return 0;
}

static int lt(item_t a, item_t b)
{
    return a < b;
}

static void swap(item_t *a, item_t *b)
{
    item_t tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

/* the original quick_sort */
void quick_sort1(item_t *a, int l, int r)
{
    if (r <= l) {
        return;
    }

    int i = partition(a, l, r);
    quick_sort1(a, l, i - 1);
    quick_sort1(a, i + 1, r);
}

/* the modified quick_sort, which will return directly if all the keys in the
 * subfiles are equal */
void quick_sort2(item_t *a, int l, int r)
{
    if (r <= l) {
        return ;
    }

    int i = partition2(a, l, r);
    quick_sort2(a, l, i - 1);
    quick_sort2(a, i + 1, r);
}


static int partition(item_t *a, int l, int r)
{
    int i    = l - 1;
    int j    = r;
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j]) && j > l) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}

/* in this partition, we will scan over keys equal to the partition element
 * instead of stopping the scan when we encounter them */
static int partition2(item_t *a, int l, int r)
{
    int i    = l - 1;
    int j    = r;
    item_t v = a[r];

    for (; ;) {
        while (le(a[++i], v) && i < r) ;

        while (le(v, a[--j]) && j > l) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}

int le(item_t a, item_t b)
{
    return lt(a, b) || (!lt(a, b) && !lt(b, a));
}

void insertion_sort(item_t *a, int l, int r)
{
    /* find the min value as the sentinel */
    int min;
    int i;

    for (min = l, i = min + 1; i <= r; i++) {
        if (a[min] > a[i]) {
            min = i;
        }
    }

    for (i = l + 1; i <= r; i++) {
        int j    = i;
        item_t v = a[j];

        for (; lt(v, a[j-1]); j--) {
            a[j] = a[j-1];
        }

        a[j] = v;
    }
}

int comp(const void *l, const void *r)
{
    item_t a = *(item_t *)l;
    item_t b = *(item_t *)r;
    return a - b;
}

void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; first++) {
        f(first);
    }
}

void print(item_t *x)
{
    printf("%d\n", *x);
}

void init(item_t *x)
{
    *x = rand() % MAX;
}

