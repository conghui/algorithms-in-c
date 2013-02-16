#include <stdio.h>

#include "btree.h"

int main(void)
{
    btree_t bt;
    bt = btree_init();
    printf("leaf count: %d\n", btree_leaf_count(bt));
    btree_finalize(&bt);
    return 0;
}
