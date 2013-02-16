#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1024
typedef int item_t;

static item_t aux[MAXSIZE];
void mersort2(item_t *a, int l, int r);
void merge3(item_t *a, int l, int m1, int m2, int r);
void mergesort3(item_t *a, int l, int r);
void merge2(item_t *a, int l, int m, int r);
void mergesort2(item_t *a, int l, int r);
void arraycpy(item_t *dest, item_t *src, int n);
void print(item_t *a, int n);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void init(item_t *x);
int eq(item_t *a, item_t *b, int n);

void merge3(item_t *a, int l, int m1, int m2, int r)
{
    int i = l;
    int j = m1;
    int k = m2;
    int t;
    /* copy array a into array aux */
    arraycpy(aux + l, a + l, (r-l+1));

    for (t = l; t <= r; t++) {
        if (i < m1 && j < m2 && k <= r) { /* each subarray has element */
            if (aux[i] <= aux[j] && aux[i] <= aux[k]) {
                a[t] = aux[i++];
            } else if (aux[j] <= aux[i] && aux[j] <= aux[k]) {
                a[t] = aux[j++];
            } else if (aux[k] <= aux[i] && aux[k] <= aux[j]) {
                a[t] = aux[k++];
            }
        } else if (i == m1 && j < m2 && k <= r) {
            a[t] = aux[j] <= aux[k] ? aux[j++] : aux[k++];
        } else if (j == m2 && i < m1 && k <= r) {
            a[t] = aux[i] <= aux[k] ? aux[i++] : aux[k++];
        } else if (k > r && i < m1 && j < m2) {
            a[t] = aux[i] <= aux[j] ? aux[i++] : aux[j++];
        } else if (i < m1 && j == m2 && k > r) {
            a[t] = aux[i++];
        } else if (j < m2 && i == m1 && k > r) {
            a[t] = aux[j++];
        } else if (k <= r && i == m1 && j == m2) {
            a[t] = aux[k++];
        }
    }
}

void mergesort3(item_t *a, int l, int r)
{
    if (r -l <= 1) {
        return ;
    }

    int interval = (r-l + 1) / 3;
    int m1       = l + interval;
    int m2       = m1 + interval;
    mergesort3(a, l, m1-1);
    mergesort3(a, m1, m2-1);
    mergesort3(a, m2, r);
    merge3(a, l, m1, m2, r);
}

void merge2(item_t *a, int l, int m, int r)
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

void mergesort2(item_t *a, int l, int r)
{
    if (r <= l) {
        return;
    }

    int m = l + ((r-l) >> 1);
    mergesort2(a, l, m);
    mergesort2(a, m + 1, r);
    merge2(a, l, m, r);
}

int main(void)
{
    int n     = 100;
    item_t *a = malloc(n * sizeof *a);
    item_t *b = malloc(n * sizeof *b);
    for_each(a, a + n, init);
    arraycpy(b, a, n);
    mergesort3(a, 0, n-1);
    mergesort2(b, 0, n-1);

    if (eq(a, b, n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
        print(a, n);
        print(b, n);
    }

    free(a);
    free(b);
    return 0;
}

void arraycpy(item_t *dest, item_t *src, int n)
{
    item_t *last = src + n;

    while (src != last) {
        *dest++ = *src++;
    }
}

void print(item_t *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    putchar('\n');
}

void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; ++first) {
        f(first);
    }
}

void init(item_t *x)
{
    *x = rand();
}

int eq(item_t *a, item_t *b, int n)
{
    return memcmp(a, b, n * sizeof *a) == 0;
}
