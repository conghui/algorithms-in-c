#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "bst.h"

#define MAX INT_MAX
#define SIZE(A) (sizeof(A) / sizeof(*(A)))

int main(void)
{
    size_t i;
    size_t n = 1000;
    bst_t bst1;

    for (; n < 1000000; n *= 10) {
        bst1 = bst_init();

        for (i = 0; i < n; i++)  {
            bst_insert(bst1, rand() % MAX);
        }

        bst_finalize(&bst1);
    }

    return 0;
}
