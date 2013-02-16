#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX RAND_MAX

typedef int item_t;

static int lt(item_t a, item_t b);
static void swap(item_t *a, item_t *b);
static int same(item_t *a, int l, int r);
static int partition(item_t *a, int l, int r);
void quick_sort1(item_t *a, int l, int r);
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
    quick_sort1(a, 0, n-1);
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
    if (same(a, l, r)) {
        return ;
    }

    int i = partition(a, l, r);
    quick_sort2(a, l, i - 1);
    quick_sort2(a, i + 1, r);
}

static int same(item_t *a, int l, int r)
{
    for (; l <= r - 1; l++) {
        if (a[l] != a[l+1]) {
            return 0;
        }
    }

    return 1;
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
