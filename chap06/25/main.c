#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int item_t;
static void sort(item_t *a, int l, int r);
static void swap(item_t *a, item_t *b);

/* bubble sort */
static void sort(item_t *a, int l, int r)
{
    int i;
    int j;

    for (i = l; i < r; i++) {
        for (j = r; j > i; j--) {
            if (a[j] < a[j-1]) {
                swap(&a[j], &a[j-1]);
            }
        }
    }
}

static void swap(item_t *a, item_t *b)
{
    item_t tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

static void print(item_t *a, int l, int r)
{
    for (; l < r; l++) {
        printf("%3d ", a[l]);
    }

    putchar('\n');
}

static void init(item_t *a, int l, int r)
{
    for (; l < r; l++) {
        a[l] = rand() % 100;
    }
}

int main(void)
{
    int N  = 20;
    int *a = malloc(N * sizeof *a);
    init(a, 0, N-1);
    print(a, 0, N-1);
    sort(a, 0, N-1);
    print(a, 0, N-1);
    return 0;
}
