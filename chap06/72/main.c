#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int item_t;

static void findmaxmin(item_t *a, int l, int r, int *max, int *min);
void keyindex_sort(item_t *a, int l, int r);
void init(int *x);
void show(int *x);
void for_each(item_t *a, int n, void (*visit)(int *));

void keyindex_sort(item_t *a, int l, int r)
{
    int max, min;
    findmaxmin(a, l, r, &max, &min);
    int cntsize = max - min + 1;
    item_t *cnt = malloc(cntsize * sizeof *cnt);
    /* print the max value for testing */
    printf("min:%d max:%d, size: %d\n", min, max, cntsize);
    memset(cnt, 0, cntsize * *cnt); /* cleat the counter */

    for (int i = l; i <= r; i++) {
        cnt[a[i] - min]++;
    }

    item_t total = 0;

    for (int i = 0; i < cntsize; i++) {
        item_t tmp = cnt[i];
        cnt[i]     = total;
        total     += tmp;
    }

    item_t *b = malloc((r-l + 1) * sizeof *a);

    for (int i = l; i <= r; i++) {
        b[cnt[a[i] - min]++] = a[i];
    }

    memcpy(a, b, (r-l+1) * sizeof *a);
    free(cnt);
    free(b);
}

int main(void)
{
    int n     = 20;
    item_t *a = malloc(n * sizeof *a);
    for_each(a, n, init);
    for_each(a, n, show);
    putchar('\n');
    keyindex_sort(a, 0, n-1);
    for_each(a, n, show);
    putchar('\n');
    return 0;
}

void init(int *x)
{
    *x = rand() % 100;
}

void show(int *x)
{
    printf("%3d ", *x);
}

void for_each(item_t *a, int n, void (*visit)(int *))
{
    for (int i = 0; i < n; i++) {
        visit(a + i);
    }
}

static void findmaxmin(item_t *a, int l, int r, int *max, int *min)
{
    if (l >= r) {
        *max = *min = a[l];
        return ;
    } else if (l == r - 1) {
        *max = a[l] > a[r] ? a[l] : a[r];
        *min = a[l] < a[r] ? a[l] : a[r];
        return ;
    }

    int max1, min1;
    int max2, min2;
    int mid = l + (r-l) / 2;
    findmaxmin(a, l, mid, &max1, &min1);
    findmaxmin(a, mid + 1, r, &max2, &min2);
    *max = max1 > max2 ? max1 : max2;
    *min = min1 < min2 ? min1 : min2;
}
