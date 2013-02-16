#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int item_t;
static void *alloc(size_t size);
void merge(item_t *a, int l, int m, int r);
void print(item_t *a, int n);

void merge(item_t *a, int l, int m, int r)
{
    item_t *aux = alloc((r-l+1) * sizeof *aux);
    int i;
    int j;

    for (i = m + 1; i > l; i--) {
        aux[i-1] = a[i-1];
    }

    for (j = m; j < r; j++) {
        aux[r-(j-m)] = a[j + 1];
    }

    int k;
    print(aux, 12);

    for (k = l; k <= r; k++) {
        a[k] = aux[i] < aux[j] ? aux[i++] : aux[j--];
    }

    free(aux);
}

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

int main(void)
{
    int a[] = {'A', 'E', 'Q', 'S', 'U', 'Y', 'E', 'I', 'N', 'O', 'S', 'T'};
    print(a, 12);
    merge(a, 0, 5, 11);
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
