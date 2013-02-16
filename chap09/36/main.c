#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "glovar.h"
#include "util.h"
#include "heap.h"
#include "qsort.h"

int main(void)
{
    int n = 1000000;
    int k = 10;

    for (; k <= n; k *= 10) {
        item_t *a = alloc(n * sizeof *a);
        item_t *b = alloc(n * sizeof *a);
        generate(a, a + n, randNum);
        memcpy(b, a, n * sizeof *b);

        if (k < n/2) {
            hselect(a, n, k, gt);
        } else {
            hselect(a, n, n-k, lt);
        }

        qselect(b, n, k);
        putchar('\n');
        free(a);
        free(b);
    }

    return 0;
}
