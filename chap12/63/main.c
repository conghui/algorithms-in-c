#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "bst.h"

#define MAX 20
#define SIZE(A) (sizeof(A) / sizeof(*(A)))
void print(item_t x);

int main(void)
{
    size_t i;
    size_t n = 10;
    bst_t bst1;
    srand(2);
    bst1 = bst_init(n);

    for (i = 0; i < n; i++)  {
        item_t t = rand() % MAX;
        bst_insert(bst1, t);
    }

    bst_sort(bst1, print);
    putchar('\n');
    bst_finalize(&bst1);
    return 0;
}

void print(item_t x)
{
    printf("%3d ", x);
}
