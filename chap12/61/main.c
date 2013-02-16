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

        printf("for n = %u: The max comparision of the tree is: %u\n",
               n, bst_maxcompare(bst1));
        printf("for n = %u: The average search hit of the tree is:%.2f\n",
               n, bst_avg_hit(bst1));
        printf("for n = %u: The average search miss of the tree is: %.2f\n\n",
               n, bst_avg_miss(bst1));
        bst_finalize(&bst1);
    }

    return 0;
}
