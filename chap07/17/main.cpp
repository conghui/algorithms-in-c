#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <stack>
#include <queue>

using namespace std;

typedef int item_t;

static int partition(item_t *a, int l, int r);
static int lt(item_t a, item_t b);
static void swap(item_t *a, item_t *b);
static void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void quick_sort(item_t *a, int l, int r);
void init(item_t *x);
void print(item_t *x);

int main(void)
{
    int n = 20;
    item_t *a = (item_t *)malloc(n * sizeof *a);
    for_each(a, a + n, init);
    for_each(a, a + n, print);
    putchar('\n');
    quick_sort(a, 0, n-1);
    for_each(a, a + n, print);
    putchar('\n');
    return 0;
}

void quick_sort(item_t *a, int l, int r)
{
    queue<pair<int, int> > stk;
    stk.push(make_pair(l, r));

    while (!stk.empty()) {
        l = stk.front().first;
        r = stk.front().second;
        stk.pop();

        if (l >= r) {
            continue;
        }

        int i = partition(a, l, r);

        if (r - i > 1) {
            stk.push(make_pair(i + 1, r));
        }

        if (i - l > 1) {
            stk.push(make_pair(l, i-1));
        }
    }
}

static int partition(item_t *a, int l, int r)
{
    int i    = l - 1;
    int j    = r;
    item_t v = a[r];

    for (;;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j]) && j != l) ;

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
    *x = rand() % 100;
}

void print(item_t *x)
{
    printf("%3d ", *x);
}
