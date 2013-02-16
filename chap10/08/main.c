#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define WORD_BIT (CHAR_BIT * sizeof(int))

#define digit(A, B) \
    (((A) >> (WORD_BIT - ((B)+1))) & 1)

#define MAX INT_MAX
#define FROM_BIT 0

typedef int item_t;
typedef item_t *iterator_t;
typedef item_t (*function_t)();

static void swap(item_t *a, item_t *b);
inline static int lt(item_t a, item_t b);
void _quick_sortB(item_t *a, int l, int r, size_t w);
int partitionB(item_t *a, int l, int r, size_t w);
void quicksortB(item_t *a, int l, int r);
void generate(iterator_t first, iterator_t last, function_t f);
item_t rand_num();
void print(item_t *a, int n);
int comp(const void *l, const void *r);
void quicksort(item_t *a, int l, int r);
int partition(item_t *a, int l, int r);

int main(void)
{
    int n     = 1000000;
    clock_t begin, end;
    item_t *a = malloc(n * sizeof *a);
    item_t *b = malloc(n * sizeof *b);
    generate(a, a + n, rand_num);
    memcpy(b, a, n * sizeof *b);
    begin = clock();
    quicksortB(a, 0, n - 1);
    end = clock();
    double sec = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Binary quick sort use: %.3f seconds\n", sec);
    begin = clock();
    quicksort(b, 0, n - 1);
    end = clock();
    sec = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Standard quick sort use: %.3f seconds\n", sec);
    const char *result = memcmp(a, b, n * sizeof *a) == 0 ? "Correct" : "Wrong";
    puts(result);
    free(a);
    free(b);
    return 0;
}

void _quick_sortB(item_t *a, int l, int r, size_t w)
{
    if (r <= l || w > WORD_BIT) {
        return ;
    }

    int  j = partitionB(a, l, r, w);
    _quick_sortB(a, l, j - 1, w+1);
    _quick_sortB(a, j, r, w+1);
}

int partitionB(item_t *a, int l, int r, size_t w)
{
    int i = l;
    int j = r;

    while (i < j) {
        while (digit(a[i], w) == 0 && i < j) {
            i++;
        }

        while (digit(a[j], w) == 1 && i < j) {
            j--;
        }

        swap(&a[i], &a[j]);
    }

    /* now i == j */
    if (digit(a[r], w) == 0) {
        i++;
    }

    return i;
}

void quicksortB(item_t *a, int l, int r)
{
    _quick_sortB(a, l, r, FROM_BIT);
}

static void swap(item_t *a, item_t *b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}

void generate(iterator_t first, iterator_t last, function_t f)
{
    for (; first != last; ++first) {
        *first = f();
    }
}

item_t rand_num()
{
    return rand() % MAX;
}

void print(item_t *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%3d ", a[i]);
    }

    putchar('\n');
}

int comp(const void *l, const void *r)
{
    return *(item_t *)l - *(item_t *)r;
}

void quicksort(item_t *a, int l, int r)
{
    if (r <= l) {
        return ;
    }

    int i = partition(a, l, r);
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}

int partition(item_t *a, int l, int r)
{
    int i    = l - 1;
    int j    = r;
    item_t v = a[r];

    for (; ;) {
        while (lt(a[++i], v)) ;

        while (lt(v, a[--j]) && j != l) ;

        if (i >= j) {
            break;
        }

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);
    return i;
}

inline static int lt(item_t a, item_t b)
{
    return a < b;
}
