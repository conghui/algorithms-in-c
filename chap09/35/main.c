#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 100

typedef int item_t;
typedef item_t *Iterator;
typedef item_t (*Generator)();
typedef void (*Function)(item_t *);

static void *alloc(size_t size);
void print(item_t *x);
item_t randNum();
void for_each(Iterator first, Iterator last, Function f);
void generate(Iterator first, Iterator last, Generator gen);
void selection(item_t *a, int n, int k);
void make_heap(Iterator first, Iterator last);
void fixdown(item_t *a, int k, int n);
void push_heap(Iterator first, Iterator last);
void pop_heap(Iterator first, Iterator last);
void swap(Iterator a, Iterator b);
void fixup(item_t *a, int k);
int lt(item_t a, item_t b);
int comp(const void *l, const void *r);

int main(void)
{
    int n     = 10;
    item_t *a = alloc(n * sizeof *a);
    generate(a, a + n, randNum);
    for_each(a, a + n, print);
    putchar('\n');
    qsort(a, n, sizeof *a, comp);
    for_each(a, a + n, print);
    putchar('\n');
    selection(a, n, 3);
    free(a);
    return 0;
}


void print(item_t *x)
{
    printf("%3d ", *x);
}

item_t randNum()
{
    return rand() % MAX;
}

void for_each(Iterator first, Iterator last, Function f)
{
    while (first != last) {
        f(first++);
    }
}

void generate(Iterator first, Iterator last, Generator gen)
{
    while (first != last) {
        *first++ = gen();
    }
}

void selection(item_t *a, int n, int k)
{
    void *alloc(size_t size);
    /* b is a heap */
    item_t *b = alloc((k+2) * sizeof *b);
    /* copy the first k elements into the heap */
    memcpy(b, a, k * sizeof *b);
    /* make a heap with k elements */
    make_heap(b, b + k);
    int i;

    for (i = k; i < n; i++) {
        b[k] = a[i];
        push_heap(b, b + k + 1);
        pop_heap(b, b + k + 1);
    }

    printf("The %dth smallest element is: %d\n", k, *b);
    free(b);
}

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

void make_heap(Iterator first, Iterator last)
{
    int n = last - first;
    int k;

    for (k = n/2; k >= 1; k--) {
        fixdown(first - 1, k, n);
    }
}

void fixdown(item_t *a, int k, int n)
{
    item_t v = a[k];
    int j;

    while ((j = 2 * k) <= n) {
        if (j < n && lt(a[j], a[j+1])) {
            j++;
        }

        if (!lt(v, a[j])) {
            break;
        }

        a[k] = a[j];
        k    = j;
    }

    a[k] = v;
}

/* [first last-1) is already a heap, and extend the heap
 * to [first, last)
 * */
void push_heap(Iterator first, Iterator last)
{
    /* the position of the last element*/
    int k = last - first;
    fixup(first - 1, k);
}

void pop_heap(Iterator first, Iterator last)
{
    swap(first, last - 1);
    fixdown(first - 1, 1, last - first - 1);
}

void swap(Iterator a, Iterator b)
{
    item_t tmp = *a;
    *a         = *b;
    *b         = tmp;
}
void fixup(item_t *a, int k)
{
    item_t v = a[k];

    while (k > 1 && lt(a[k/2], v)) {
        a[k] = a[k/2];
        k /= 2;
    }

    a[k] = v;
}

int lt(item_t a, item_t b)
{
    return a < b;
}

int comp(const void *l, const void *r)
{
    return *(item_t *)l - *(item_t *)r;
}
