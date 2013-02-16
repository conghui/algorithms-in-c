#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXSIZE 1000000

typedef int item_t;
void merge(item_t *a, int l, int m, int r);
void print(item_t *a, int n);

void merge_sort(item_t *a, int l, int r)
{
    if (r <= l) {
        return;
    }

    /*int m = l + ((r-l) >> 1);*/
    int m = (r+l) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m+1, r);
    merge(a, l, m, r);
}

static int aux[MAXSIZE];

void merge(item_t *a, int l, int m, int r)
{
    int i, j, k;

    for (i = m + 1; i > l; i--) {
        aux[i-1] = a[i-1];
    }

    for (j = m; j < r; j++) {
        aux[r+m-j] = a[j+1];
    }

    for (k = l; k <= r; k++) {
        a[k] = aux[i] <= aux[j] ? aux[i++] : aux[j--];
    }
}

int main(void)
{
    int a[] = {'E', 'A', 'S', 'Y', 'Q', 'U', 'E', 'S', 'T', 'I', 'O', 'N'};
    print(a, 12);
    merge_sort(a, 0, 11);
    print(a, 12);
    return 0;
}

void print(item_t *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%2c ", a[i]);
    }

    putchar('\n');
}
