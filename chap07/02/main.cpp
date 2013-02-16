#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <stack>

using namespace std;

typedef int item_t;
static void quick_sort(item_t *a, int l, int r);
static int partition(item_t *a, int L, int R);
static int less(item_t a, item_t b);
static void exch(item_t *a, item_t *b);
static void for_each(item_t *first, item_t *last, void (*f)(item_t *));

void init(item_t   *x) ;
void print(item_t  *x) ;

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

static void quick_sort(item_t *a, int l, int r)
{
    stack<int> stk;
    stk.push(r);
    stk.push(l);

    while (!stk.empty()) {
        l = stk.top();
        stk.pop();
        r = stk.top();
        stk.pop();

        if (l >= r) {
            continue;
        }

        int i = partition(a, l, r);
        stk.push(i-1);
        stk.push(l);
        stk.push(r);
        stk.push(i+1);
    }
}

static int partition(item_t *a, int L, int R)
{
    int i     = L - 1;
    int j     = R;
    int pivot = a[R];

    for (; ;) {
        while (less(a[++i], pivot)) ;

        while (less(pivot, a[--j]) && j > L) ;

        if (j <= i) {
            break;
        }

        exch(&a[i], &a[j]);
    }

    exch(&a[i], &a[R]);
    return i;
}

static int less(item_t a, item_t b)
{
    return a < b;
}

static void exch(item_t *a, item_t *b)
{
    item_t tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
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
