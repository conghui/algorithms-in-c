#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define MAX 100

int main(void)
{
    int n;
    int i;
    bst_t bst1;
    bst1 = bst_init();

    n = 10;
    for (i = 0; i < n; i++) {
        bst_insert(bst1, n);
    }

    bst_sort(bst1);

    bst_delete(bst1, n);

    bst_sort(bst1);
    bst_finalize(&bst1);
    return 0;
}
