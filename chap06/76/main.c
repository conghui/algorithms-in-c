#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define N 20

typedef struct {
    int key;
    char str[128];
} *item_t;

static void *alloc(size_t size);
static void findmaxmin(item_t *a, int l, int r, int *max, int *min);
static void accumulate(int *a, int l, int r);
void clear(item_t *a, int n);
void for_each(item_t *a, int n, void (*visit)(item_t *));
item_t item_init(int key);
void init(item_t *x);
void print(item_t *x);
void counting_sort(item_t *a, int l, int r);

int main(void)
{
    item_t a[N];
    for_each(a, N, init);
    for_each(a, N, print);
    putchar('\n');
    counting_sort(a, 0, N-1);
    for_each(a, N, print);
    putchar('\n');
    clear(a, N);
    return 0;
}

void clear(item_t *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        free(a[i]);
    }
}
void for_each(item_t *a, int n, void (*visit)(item_t *))
{
    int i;

    for (i = 0; i < n; i++) {
        visit(a + i);
    }
}

item_t item_init(int key)
{
    item_t t = alloc(sizeof *t);
    t->key   = key;
    return t;
}
void init(item_t *x)
{
    *x = item_init(rand() % 30);
}

void print(item_t *x)
{
    printf("%3d ", (*x)->key);
}

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

void counting_sort(item_t *a, int l, int r)
{
    int i;
    int max, min;
    int cntsize;
    int asize;
    int *cnt;
    item_t *b;
    findmaxmin(a, l, r, &max, &min);
    cntsize = max - min + 1;
    asize = r - l + 1;
    cnt = alloc(cntsize * sizeof *cnt);
    b   = alloc(asize * sizeof *b);
    memset(cnt, 0, cntsize * sizeof *cnt);

    for (i = l; i <= r; i++) {
        cnt[a[i]->key - min]++;
    }

    accumulate(cnt, 0, cntsize-1);

    for (i = l ; i <= r; i++) {
        b[cnt[a[i]->key - min]++] = a[i];
    }

    memcpy(a, b, asize * sizeof *a);
    free(b);
    free(cnt);
}

static void findmaxmin(item_t *a, int l, int r, int *max, int *min)
{
    if (l >= r) {
        *max = *min = a[l]->key;
    } else if (l == r - 1) {
        *max = a[l]->key > a[r]->key ? a[l]->key : a[r]->key;
        *min = a[l]->key < a[r]->key ? a[l]->key : a[r]->key;
    } else {
        int mid = l + (r-l)/2;
        int max1, max2, min1, min2;
        findmaxmin(a, l, mid, &max1, &min1);
        findmaxmin(a, mid+1, r, &max2, &min2);
        *max = max1 > max2 ? max1 : max2;
        *min = min1 < min2 ? min1 : min2;
    }
}

static void accumulate(int *a, int l, int r)
{
    int i;
    int total = 0;

    for (i = l; i <= r; i++) {
        int tmp = a[i];
        a[i]    = total;
        total  += tmp;
    }
}
