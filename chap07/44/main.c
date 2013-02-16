#include <stdio.h>
#include <stdlib.h>

#define MAX 100
typedef int item_t;

static void partial_sort(item_t *a, int l, int r, int m);
static int partition(item_t *a, int l, int r);
static int lt(item_t a, item_t b);
static void swap(item_t *a, item_t *b);
void init(item_t *x);
void print(item_t *x);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));

static void partial_sort(item_t *a, int l, int r, int m)
{
    if (r == m -1 || l == m + 1) {
        return ;
    }

    int i = partition(a, l, r);

    if (i < m) { /* the left side if ok, sort the right part */
        partial_sort(a, i + 1, r, m);
    } else { /* the right side if ok, sort the left half */
        partial_sort(a, l, i - 1, m);
    }
}

static int partition(item_t *a, int l, int r)
{
    int i    = l - 1;
    int j    = r;
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v));

        while (lt(v, a[--j]) && j != l) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}


static int lt(item_t a, item_t b)
{
    return a < b;
}

static void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}
int main(void)
{
    int n = 11;
    item_t *a = malloc(n * sizeof *a);
    for_each(a, a + n, init);
    for_each(a, a + n, print);
    putchar('\n');
    partial_sort(a, 0, n - 1, n/2);
    for_each(a, a + n, print);
    putchar('\n');
    return 0;
}

void init(item_t *x)
{
    *x = rand() % MAX;
}

void print(item_t *x)
{
    printf("%3d ", *x);
}

void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; first++) {
        f(first);
    }
}
