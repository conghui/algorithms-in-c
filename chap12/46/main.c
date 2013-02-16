#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
static void print(item_t x);

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

    printf("The number of times that need to compare is: %u\n",
           compare_cnt);
    bst_sort(bst1, print);
    putchar('\n');
    bst_finalize(&bst1);
    return 0;
}

static void print(item_t x)
{
    printf("%2c ", x);
}
