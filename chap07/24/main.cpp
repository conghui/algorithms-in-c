#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include <stack>

typedef int item_t;

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
    int n = 10000000;
    clock_t begin, end;
    item_t *a = (item_t *)malloc(n * sizeof *a);
    for_each(a, a + n, init);
    //for_each(a, a + n, print); putchar('\n');
    begin = clock();
    //qsort(a, n, sizeof *a, comp);
    //std::sort(a, a + n);
    quick_sort(a, 0, n-1);
    insertion_sort(a, 0, n-1);
    end = clock();
    //for_each(a, a + n, print); putchar('\n');
    printf("# com / # element: %f\n", (double)comp_times / n);
    printf("time elapse: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
    free(a);
    return 0;
}

void quick_sort(item_t *a, int l, int r)
{
    static const int M = 20;
    std::stack<std::pair<int, int> > stk;
    stk.push(std::make_pair(l, r));

    while (!stk.empty()) {
        l = stk.top().first;
        r = stk.top().second;
        stk.pop();

        if (r - l <= M) {
            continue;
        }

        int i = partition(a, l, r);

        if (r - i > M) {
            stk.push(std::make_pair(i+1, r));
        }

        if (i - l > M) {
            stk.push(std::make_pair(l, i - 1));
        }
    }
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
    return a < b;
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
    *x = rand() % RAND_MAX;
}

void print(item_t *x)
{
    printf("%3d ", *x);
}

void insertion_sort(item_t *a, int l, int r)
{
    int i;

    for (i = l + 1; i <= r; i++) {
        int j    = i;
        item_t v = a[j];

        for (; j >= l + 1 && lt(v, a[j-1]); j--) {
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
