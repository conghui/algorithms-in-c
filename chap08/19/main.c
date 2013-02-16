#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define M 10
#define MAX 1000000
#define MAXSIZE 10000000
typedef int item_t;
static void *alloc(size_t size);
static void arraycpy(item_t *dest, item_t *src, int n);
static int arrayeq(item_t *a, item_t *b, int n);
static int comp(const void *l, const void *r);
void mergesortABr(item_t *a, item_t *b, int l, int r);
void mergesortAB(item_t *a, int l, int r);
void mergeAB(item_t *c, item_t *a, int n, item_t *b, int m);
void insertion_sort(item_t *a, int l, int r);
void swap(item_t *a, item_t *b);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void init(item_t *x);
void print(item_t *x);

void mergesortABr(item_t *a, item_t *b, int l, int r)
{
    if (r - l <= M) {
        insertion_sort(a, l, r);
        return;
    }

    int m = l + ((r-l) >> 1);
    mergesortABr(b, a, l, m);
    mergesortABr(b, a, m + 1, r);
    mergeAB(a + l, b + l, m -l + 1, b + m + 1, r - m);
}

void mergesortAB(item_t *a, int l, int r)
{
    static item_t aux[MAXSIZE];
    memcpy(aux, a, (r-l+1)*sizeof *aux);
    mergesortABr(a, aux, l, r);
}

void mergeAB(item_t *c, item_t *a, int n, item_t *b, int m)
{
    int i, j, k;

    for (i = j = k = 0; k < n + m; k++) {
        if (i == n) {
            c[k] = b[j++];
            continue;
        }

        if (j == m) {
            c[k] = a[i++];
            continue;
        }

        c[k] = a[i] <= b[j] ? a[i++] : b[j++];
    }
}

void insertion_sort(item_t *a, int l, int r)
{
    int i, min;

    for (min = l, i = l + 1; i <= r; i++)
        if (a[min] > a[i]) {
            min = i;
        }

    swap(&a[min], &a[l]);

    for (i = l + 1; i <= r; i++) {
        int j    = i;
        item_t v = a[j];

        for (; v < a[j-1]; j--) {
            a[j] = a[j-1];
        }

        a[j] = v;
    }
}

void merge(item_t *a, int l, int m, int r)
{
    static item_t aux[MAXSIZE];
    int i, j, k;

    for (i = m + 1; i > l; i--) {
        aux[i-1] = a[i - 1];
    }

    for (j = m; j < r; j++) {
        aux[r+m-j] = a[j+1];
    }

    for (k = l; k <= r; k++) {
        a[k] = aux[i] <= aux[j] ? aux[i++] : aux[j--];
    }
}

void mergesort(item_t *a, int l, int r)
{
    if (r - l <= M) {
        insertion_sort(a, l, r);
        return ;
    }

    int m = l + ((r - l) >> 1);
    mergesort(a, l, m);
    mergesort(a, m + 1, r);
    merge(a, l, m, r);
}

void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

int main(void)
{
    int n  = 1000000;
    clock_t begin, end;
    int *a = alloc(n * sizeof *a);
    int *b = alloc(n * sizeof *b);
    begin = clock();
    for_each(a, a + n, init);
    arraycpy(b, a, n);
    mergesortAB(a, 0, n-1);
    /*insertion_sort(b, 0, n-1);*/
    /*qsort(b, n, sizeof *a, comp);*/
    mergesort(b, 0, n - 1);

    if (arrayeq(a, b, n)) {
        end = clock();
        printf("Time elapse: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);
        printf("Yes\n");
    } else {
        printf("No\n");
        /*for_each(a, a + n, print); putchar('\n'); putchar('\n');*/
        /*for_each(b, b + n, print); putchar('\n');*/
    }

    return 0;
}

void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; ++first) {
        f(first);
    }
}

void init(item_t *x)
{
    *x = rand() % MAX;
}

void print(item_t *x)
{
    printf("%3d ", *x);
}

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static void arraycpy(item_t *dest, item_t *src, int n)
{
    memcpy(dest, src, n * sizeof *src);
}

static int arrayeq(item_t *a, item_t *b, int n)
{
    return memcmp(a, b, n * sizeof *a) == 0;
}


static int comp(const void *l, const void *r)
{
    return *(item_t *)l - *(item_t *)r;
}
