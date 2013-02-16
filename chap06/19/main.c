#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int item_t;
static void sort(item_t *a, int l, int r);
static void set_sentinel(item_t *a, int l, int r);
static inline void swap(item_t *a, item_t *b);
static inline int less(item_t a, item_t b);
static void rand_array(item_t *a, int size);
static void print(item_t *a, int size);

int main(void)
{
    int N = 20;
    int *a = malloc(N * sizeof *a);
    assert(a);
    rand_array(a, N);
    print(a, N);
    sort(a, 0, N-1);
    print(a, N);
    return 0;
}


/**
 * @brief insertion sort of array a
 *
 * @param a the array to be sorted
 * @param l lower bound of the array
 * @param r upper bound of the array
 */
static void sort(item_t *a, int l, int r)
{
    int i;
    /* find the smallest element, and switch it with the first element */
    set_sentinel(a, l, r);

    for (i = l+2; i <= r; i++) {
        int j    = i;
        item_t v = a[j];

        while (less(v, a[j-1])) {
            a[j] = a[j-1];
            j--;
        }

        a[j] = v;
    }
}

static void set_sentinel(item_t *a, int l, int r)
{
    int i;
    int min = l;

    for (i = l + 1; i <= r; i++) {
        if (a[i] < a[min]) {
            min = i;
        }
    }

    swap(&a[0], &a[min]);
}

static inline void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

static inline int less(item_t a, item_t b)
{
    return a < b;
}

static void rand_array(item_t *a, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        a[i] = rand() % 100;
    }
}

static void print(item_t *a, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf("%3d ", a[i]);
    }

    putchar('\n');
}
