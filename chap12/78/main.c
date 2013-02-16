#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define MAX 100

int main(void)
{
    int n;
    int i;
    bst_t bst1;
    bst_t bst2;
    bst1 = bst_init();
    bst2 = bst_init();

    n = 10;
    for (i = 0; i < n; i++) {
        bst_insert(bst1, rand() % MAX);
        bst_insert(bst2, rand() % MAX);
    }

    bst_sort(bst1);

    printf("the 3th (count from 0) smallest key is: %d\n", bst_select(bst1, 3));

    printf("\n\nNow we partition the tree at the 5th (count from 0) element:\n");
    bst_partition(bst1, 5);
    bst_sort(bst1);

    while (!bst_empty(bst1)) {
        int key = bst_select(bst1, 0);
        printf("\nDelete key %d, the remaining is: \n", key);
        bst_delete(bst1, key);
        bst_sort(bst1);
    }
    /* now we join the two tree */
    /*bst_join(bst1, bst2);*/

    /*printf("After the join, the tree is: \n");*/
    /*bst_sort(bst1);*/
    bst_finalize(&bst1);
    bst_finalize(&bst2);

    return 0;
}
