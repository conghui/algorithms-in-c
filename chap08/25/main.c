#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define M 5
#define MAX RAND_MAX
#define MAXSIZE 10000000

typedef int item_t;
void mergesortBU(item_t *a, int l, int r);
void merge(item_t *a, int l, int m, int r);
void mergesortTD(item_t *a, int l, int r);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void init(item_t *x);
void print(item_t *x);
void insertion_sort(item_t *a, int l, int r);
void swap(item_t *a, item_t *b);

int main(void)
{
    int n     = 10000000;
    clock_t begin, end;
    item_t *a = malloc(n * sizeof *a);
    item_t *b = malloc(n * sizeof *b);
    for_each(a, a + n, init);
    memcpy(b, a, n * sizeof *a);
    begin = clock();
    mergesortBU(a, 0, n - 1);
    end = clock();
    printf("Bottom up cost: %.2f sec\n",
           (double)(end - begin)/CLOCKS_PER_SEC);
    begin = clock();
    mergesortTD(b, 0, n - 1);
    end = clock();
    printf("Top down cost:  %.2f sec\n",
           (double)(end - begin)/CLOCKS_PER_SEC);

    if (memcmp(a, b, n * sizeof *a) == 0) {
        printf("Yes\n");
    } else {
        printf("No\n");
        /*for_each(a, a + n, print); putchar('\n');*/
        /*for_each(b, b + n, print); putchar('\n');*/
    }

    free(a);
    free(b);
    return 0;
}

#define min(a, b) ((a) < (b) ? (a) : (b))

void mergesortBU(item_t *a, int l, int r)
{
    int i;
    int m;

    for (i = l; i <= r - M; i += 2*M) {
        insertion_sort(a, i, min(i+2*M-1, r));
    }

    for (m = 2*M; m <= r - l +1 ; m *= 2) {
        for (i = l; i <= r - m; i += 2*m) {
            merge(a, i, i + m - 1, min(i+m+m-1, r));
        }
    }
}

void merge(item_t *a, int l, int m, int r)
{
    static item_t aux[MAXSIZE];
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

void mergesortTD(item_t *a, int l, int r)
{
    if (r - l <= M) {
        insertion_sort(a, l, r);
        return ;
    }

    int m = l + ((r-l) >> 1);
    mergesortTD(a, l, m);
    mergesortTD(a, m + 1, r);
    merge(a, l, m, r);
}

void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; ++first) {
        f(first);
    }
}

void init(item_t *x)
{
    *x = rand() % MAX;
}

void print(item_t *x)
{
    printf("%3d ", *x);
}

void insertion_sort(item_t *a, int l, int r)
{
    int i, min;

    for (min = l, i = l + 1; i <= r; i++) {
        if (a[min] > a[i]) {
            min = i;
        }
    }

    swap(&a[l], &a[min]);

    for (i = l + 1; i <= r; i++) {
        int j    = i;
        item_t v = a[j];

        for (; v < a[j-1]; j--) {
            a[j] = a[j-1];
        }

        a[j] = v;
    }
}

void swap(item_t *a, item_t *b)
{
    item_t tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}
