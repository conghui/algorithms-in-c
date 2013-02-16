#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef int item_t;
typedef int bool;
typedef item_t *ForwardIterator;

#define false 0
#define true  1
static int lt(item_t a, item_t b);
static int eq(item_t a, item_t b);
bool binary_search2(ForwardIterator first, ForwardIterator last, item_t value);
bool binary_search(ForwardIterator first, ForwardIterator last, item_t value);

int main(void)
{
    int i;
    int n     = 10;
    item_t *a = malloc(n * sizeof *a);

    for (i = 0; i < n; i++) {
        a[i] = i;
    }

    for (i = 0; i < n*1.5; i++) {
        if (binary_search2(a, a + n, i)) {
            printf("%2d is in the array\n", i);
        } else {
            printf("%2d is not in the array\n", i);
        }
    }

    return 0;
}

bool binary_search2(ForwardIterator first, ForwardIterator last, item_t value)
{
    while (first < last) {
        ForwardIterator mid = first + (last - first) / 2;

        if (eq(value, *mid)) {
            return true;
        } else if (lt(value, *mid)) {
            last = mid;
        } else {
            first = mid + 1;
        }
    }

    return false;
}

bool binary_search(ForwardIterator first, ForwardIterator last, item_t value)
{
    if (first >= last) {
        return false;
    }

    ForwardIterator mid = first + (last - first) / 2;

    if (eq(value, *mid)) {
        return true;
    } else if (lt(value, *mid)) {
        return binary_search(first, mid, value);
    } else {
        return binary_search(mid + 1, last, value);
    }
}

static int lt(item_t a, item_t b)
{
    return a < b;
}

static int eq(item_t a, item_t b)
{
    return !lt(a, b) && !lt(b,a);
}
