#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXLEN 10

typedef struct {
    int key;
    char *str;
} item_t;

static int comp_times = 0;

static int partition(item_t *a, int l, int r);
static int lt(item_t a, item_t b);
static void swap(item_t *a, item_t *b);
static void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void quick_sort(item_t *a, int l, int r);
void init(item_t *x);
void print(item_t *x);
void insertion_sort(item_t *a, int l, int r);
int comp(const void *l, const void *r);

int main(void)
{
    int n = 100000;
    clock_t begin, end;
    item_t *a = (item_t *)malloc(n * sizeof *a);
    for_each(a, a + n, init);
    /*for_each(a, a + n, print); putchar('\n');*/
    begin = clock();
    //qsort(a, n, sizeof *a, comp);
    //std::sort(a, a + n);
    /*quick_sort(a, 0, n-1);*/
    insertion_sort(a, 0, n-1);
    end = clock();
    /*for_each(a, a + n, print); putchar('\n');*/
    printf("# com / # element: %f\n", (double)comp_times / n);
    printf("time elapse: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
    int i;

    for (i = 0; i < n; i++) {
        free(a[i].str);
    }

    free(a);
    return 0;
}

void quick_sort(item_t *a, int l, int r)
{
    if (r <= l) {
        return ;
    }

    int i = partition(a, l, r);
    quick_sort(a, l, i-1);
    quick_sort(a, i + 1, r);
}

static int partition(item_t *a, int l, int r)
{
    int i    = l - 1;
    int j    = r;
    item_t v = a[r];

    for (;;) {
        while (lt(a[++i], v)) {
            comp_times++;
        }

        while (lt(v, a[--j]) && j != l) {
            comp_times++;
        }

        if (j <= i) {
            break;
        }

        swap(a + i, a + j);
    }

    swap(a + i, a + r);
    return i;
}

static int lt(item_t a, item_t b)
{
    return a.key < b.key;
}

static void swap(item_t *a, item_t *b)
{
    item_t t = *a;
    *a       = *b;
    *b       = t;
}
static void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; first++) {
        f(first);
    }
}

void init(item_t *x)
{
    x->key = rand() % 100;
    x->str = malloc(MAXLEN);
    snprintf(x->str, MAXLEN, "%d", x->key);
}

void print(item_t *x)
{
    printf("%s ", x->str);
}

void insertion_sort(item_t *a, int l, int r)
{
    int i;
    int min = l;

    for (i = l + 1; i <= r; i++) {
        if (a[min].key > a[i].key) {
            min = i;
        }
    }

    swap(&a[min], &a[l]);

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
    int a = *(int *)l;
    int b = *(int *)r;
    return a - b;
}
