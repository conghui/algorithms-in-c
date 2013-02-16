#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define MAX 100

int main(void)
{
    int n = 20;
    int i;
    bst_t bst = bst_init();

    for (i = 0; i < n; i++) {
        bst_insert(bst, rand()%MAX);
    }

    bst_sort(bst);

    /* now balance the BST */
    bst_balance(bst);
    printf("\nNow balance the BST\n");
    bst_sort(bst);
    bst_finalize(&bst);
    return 0;
}
