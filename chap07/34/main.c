#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 2

typedef int item_t;

static int lt(item_t a, item_t b);
static void swap(item_t *a, item_t *b);
static int eq(item_t a, item_t b);
static int partition(item_t *a, int l, int r);
void quick_sort(item_t *a, int l, int r);
void quick_sort2(item_t *a, int l, int r);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void print(item_t *x);
void init(item_t *x);

int main(void)
{
    int n     = 10000000;
    item_t *a = (item_t *)malloc(n * sizeof *a);
    for_each(a, a + n, init);
    /*for_each(a, a + n, print);    putchar('\n'); putchar('\n');*/
    clock_t begin = clock();
    quick_sort(a, 0, n-1);
    clock_t end = clock();
    printf("time elapse: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);
    /*for_each(a, a + n, print);    putchar('\n');*/
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

static int eq(item_t a, item_t b)
{
    return !lt(a, b) && !lt(b, a);
}

void quick_sort(item_t *a, int l, int r)
{
    if (r <= l) {
        return ;
    }

    int i    = l - 1;
    int j    = r;
    int p    = l;     /* the position to store the element same as pivot */
    int q    = r - 1; /* the position to store the element same as pivot */
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j]) && j > l) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);

        if (eq(a[i], v)) {
            swap(&a[i], &a[p++]);
        }

        if (eq(a[j], v)) {
            swap(&a[j], &a[q--]);
        }
    }

    swap(&a[i], &a[r]);
    j = i + 1; /* it should be called before the next statement */
    i = i - 1; /* the position to store element different with pivot */
    int k;

    for (k = l; k < p; k++, i--) {
        swap(&a[k], &a[i]);
    }

    for (k = r-1; k > q; k--, j++) {
        swap(&a[k], &a[j]);
    }

    quick_sort(a, l, i);
    quick_sort(a, j, r);
}

void quick_sort2(item_t *a, int l, int r)
{
    if (r <= l) {
        return ;
    }

    int i = partition(a, l, r);
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

void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; first++) {
        f(first);
    }
}

void print(item_t *x)
{
    printf("%3d ", *x);
}

void init(item_t *x)
{
    *x = rand() % MAX;
}
