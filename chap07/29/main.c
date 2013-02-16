#include <stdio.h>
#include <stdlib.h>

#define M 1
#define MAX 100

typedef int item_t;
void quick_sort(item_t *a, int l, int r);
int partition(item_t *a, int l, int r);
int lt(item_t a, item_t b);
void swap(item_t *a, item_t *b);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void print(item_t *x);
void init(item_t *x);

int main(void)
{
    int n = 5;
    item_t *a = malloc(n * sizeof *a);
    for_each(a, a + n, init);
    for_each(a, a + n, print);
    putchar('\n');
    quick_sort(a, 0, n-1);
    for_each(a, a + n, print);
    putchar('\n');
    return 0;
}

#define compexch(a, b) \
    if (lt((b),(a))) swap(&(a), &(b))

void quick_sort(item_t *a, int l, int r)
{
    if (r - l < M) {
        return;
    }

    int mid = l + ((r-l) >> 1);
    swap(&a[r-1], &a[mid]);
    compexch(a[l], a[r-1]);
    compexch(a[l], a[r]);
    compexch(a[r-1], a[r]);

    if (l+1 < r-1) {
        int i = partition(a, l+1, r-1);
        quick_sort(a, l, i-1);
        quick_sort(a, i+1, r);
    }
}

int partition(item_t *a, int l, int r)
{
    /* assure that each side has a sentinel */
    int i    = l-1;
    int j    = r;
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j])) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}

/* test if a is less than b */
int lt(item_t a, item_t b)
{
    return a < b;
}

void swap(item_t *a, item_t *b)
{
    item_t t = *a;
    *a       = *b;
    *b       = t;
}

void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; ++first) {
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
