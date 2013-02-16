#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef char item_t;
static item_t findmax(item_t *a, int l, int r);
static void *alloc(size_t size);
void keyindex_sort(item_t *a, int l, int r);
void init(item_t *x);
void print(item_t *x);
void for_each(item_t *a, size_t n, void (*visit)(item_t *));

int main(void)
{
    size_t size = 11;
    item_t *a = alloc(size * sizeof *a);
    for_each(a, size, init);
    for_each(a, size, print);
    putchar('\n');
    keyindex_sort(a, 0, size-1);
    for_each(a, size, print);
    putchar('\n');
    free(a);
    return 0;
}


void keyindex_sort(item_t *a, int l, int r)
{
    int i;
    item_t  max = findmax(a, l, r) + 1;
    int    *cnt = alloc(max *sizeof *cnt);
    item_t *b   = alloc((r-l+1) *sizeof *b);
    memset(cnt, 0, max * sizeof *cnt); /* clear the counter */

    for (i = l; i <= r; i++) {
        cnt[a[i]]++;
    }

    item_t total = 0;

    for (i = 0; i < max; i++) {
        int tmp = cnt[i];
        cnt[i]  = total;
        total  += tmp;
    }

    for (i = l; i <= r; i++) {
        b[cnt[a[i]]++] = a[i]; /* assign each element in b */
    }

    memcpy(a, b, (r-l+1) * sizeof *a);
    free(b);
    free(cnt);
}

static item_t findmax(item_t *a, int l, int r)
{
    if (l >= r) {
        return a[l];
    }

    item_t max = findmax(a, l+1, r);
    return a[l] > max ? a[l] : max;
}

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

void init(item_t *x)
{
    scanf("%c\n", x);
}

void print(item_t *x)
{
    printf("%3c ", *x);
}

void for_each(item_t *a, size_t n, void (*visit)(item_t *))
{
    size_t i;

    for (i = 0; i < n; i++) {
        visit(a + i);
    }
}
