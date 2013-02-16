#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100
/*#define USER 0*/

typedef int item_t;

void quick_sort1(item_t *a, int l, int r);
void quick_sort2(item_t *a, int l, int r);
static int lt(item_t a, item_t b);
static void swap(item_t *a, item_t *b);
int count_diff(item_t *a, int n);
int quick_sort(item_t *a, int l, int r);
int le(item_t a, item_t b);
int eq(item_t a, item_t b);
void insertion_sort(item_t *a, int l, int r);
int comp(const void *l, const void *r);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void print(item_t *x);
void init(item_t *x);

int main(void)
{
    int n     = 1E7;
    item_t *a = (item_t *)malloc(n * sizeof *a);
    for_each(a, a + n, init);
    /*for_each(a, a + n, print);    putchar('\n'); putchar('\n');*/
    clock_t begin = clock();
#if defined (USER)
    int count = quick_sort(a, 0, n-1);
    printf("Hi\n");
#else
    qsort(a, n, sizeof *a, comp);
    int count = count_diff(a, n);
#endif
    clock_t end = clock();
    /*for_each(a, a + n, print);    putchar('\n');*/
    printf("\n%d distinct number; time elapse: %f\n", count,
           (double)(end - begin)/CLOCKS_PER_SEC);
    return 0;
}

int count_diff(item_t *a, int n)
{
    int cnt = 1;
    int i;

    for (i = 0; i < n - 1; i++) {
        if (a[i] != a[i+1]) {
            cnt++;
        }
    }

    return cnt;
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

/* the original quick_sort, return # of distinct keys*/
int quick_sort(item_t *a, int l, int r)
{
    if (l == r) {
        return 1;
    }

    if (r < l) {
        return 0;
    }

    int i    = l - 1;
    int j    = r;
    int p    = l;
    int q    = r - 1;
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j]) && j != l) ;

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
    int k;
    j = i + 1;

    for (k = a[i] == a[i] ? r : r - 1; k > q; k--, j++) {
        swap(&a[k], &a[j]);
    }

    i = i - 1;

    for (k = l; k < p; k++, i--) {
        swap(&a[k], &a[i]);
    }

    int lcount = quick_sort(a, l, i);
    int rcount = quick_sort(a, j, r);
    return lcount + rcount + 1;
}

int le(item_t a, item_t b)
{
    return lt(a, b) || (!lt(a, b) && !lt(b, a));
}

int eq(item_t a, item_t b)
{
    return !lt(a, b) && !lt(b, a);
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
    printf("%3d", *x);
}

void init(item_t *x)
{
    *x = rand() % MAX;
}

