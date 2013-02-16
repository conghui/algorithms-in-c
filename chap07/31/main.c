#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef int item_t;
void quick_sort(item_t *a, int l, int r);
void compexch(item_t *a, item_t *b);
void swap(item_t *a, item_t *b);
int partition(item_t *a, int l, int r);
void for_each(item_t *first, item_t *last, void (*f)(item_t *));
void init(item_t *x);
void print(item_t *x);
void insertion_sort(item_t *a, int l, int r);

int main(void)
{
    clock_t begin, end;
    int n = 10000000;
    item_t *a = malloc(n * sizeof *a);
    for_each(a, a + n, init);
    /*for_each(a, a + n, print); putchar('\n');*/
    begin = clock();
    quick_sort(a, 0, n - 1);
    insertion_sort(a, 0, n-1);
    end = clock();
    printf("Time elapse: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);
    for_each(a, a + n, print);
    putchar('\n');
    return 0;
}

#define lt(a, b) ((a) < (b))
#define exch(a, b) { item_t tmp = a; a = b; b = tmp;}
#define compexch(a, b) if(lt(b,a)) exch(a, b)

#define M 10

void quick_sort(item_t *a, int l, int r)
{
    /*if (r - l < M) return insertion_sort(a, l, r);*/
    if (r - l < M) {
        return ;
    }

    /*exch(a[(r-l)/2], a[r-1]);*/
    /*compexch(a[l], a[r-1]);*/
    /*compexch(a[l], a[r]);*/
    /*compexch(a[r-1], a[r]);*/
    int i = partition(a, l, r);
    quick_sort(a, l, i - 1);
    quick_sort(a, i + 1, r);
}


void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a = *b;
    *b = tmp;
}
int partition(item_t *a, int l, int r)
{
    int i = l - 1;
    int j = r;
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j])) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}


void for_each(item_t *first, item_t *last, void (*f)(item_t *))
{
    for (; first != last; first++) {
        f(first);
    }
}

void init(item_t *x)
{
    *x = rand() % RAND_MAX;
}

void print(item_t *x)
{
    printf("%3d\n", *x);
}


void insertion_sort(item_t *a, int l, int r)
{
    int min = l;
    int i;

    for (i = l + 1; i <= r; i++) {
        if (a[min] > a[i]) {
            min = i;
        }
    }

    for (i = l + 1; i <= r; i++) {
        int j = i;
        item_t v = a[j];

        for (; lt(v, a[j-1]); j--) {
            a[j] = a[j-1];
        }

        a[j] = v;
    }
}
