#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define SIZE(A) (sizeof(A) / sizeof(*(A)))

int main(void)
{
    size_t i;
    int A[] = {'E', 'A', 'S', 'Y', 'Q', 'U', 'E', 'S', 'T', 'I', 'O', 'N'};
    bst_t bst1;
    bst1 = bst_init();

    for (i = 0; i < SIZE(A); i++)  {
        bst_insert(bst1, A[i]);
    }

    printf("The max comparision of the tree is: %u\n",
           bst_maxcompare(bst1));
    printf("The average comparision of the tree is:%.2f\n",
           bst_avg_compare(bst1));
    bst_finalize(&bst1);
    return 0;
}
