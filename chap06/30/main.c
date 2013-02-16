#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b);
int sort(int *a, int l, int r);

/* shaker sort: a version of bubble sort that alternate left-to-right and
 * right-to-left passes through the data */
int  sort(int *a, int l, int r)
{
    int i;
    int times = 0;

    if (l >= r) {
        return 0;
    }

    int max;
    int min;

    for (max = min = l, i = l + 1; i <= r; i++) {
        times++;

        if (a[max] < a[i]) {
            max = i;
        }

        if (a[min] > a[i]) {
            min = i;
        }
    }

    swap(&a[min], &a[l]);
    swap(&a[max], &a[r]);
    return times + sort(a, l+1, r-1);
}

static void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

int main(void)
{
    int size = 20;
    int *a;
    int i;
    a = malloc(size * sizeof *a);

    for (i = 0; i < size; i++) {
        a[i] = rand() % 100;
    }

    for (i = 0; i < size; i++) {
        printf("%3d ", a[i]);
    }

    putchar('\n');
    int times = sort(a, 0, size - 1);

    for (i = 0; i < size; i++) {
        printf("%3d ", a[i]);
    }

    printf("\ntimes: %d\n", times);
    free(a);
    return 0;
}
