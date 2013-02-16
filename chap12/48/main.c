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
        bst_search_insert(bst1, A[i]);
    }

    for (i = 0; i < SIZE(A); i++) {
        bst_search_insert(bst1, A[i]);
    }

    bst_sort(bst1, print);
    putchar('\n');
    bst_finalize(&bst1);
    return 0;
}

static void print(item_t x)
{
    printf("%2c ", x);
}
