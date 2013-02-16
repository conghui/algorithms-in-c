#include <stdio.h>

#include "btree.h"
void print(link_t l);

int main(void)
{
    btree_t bt;
    char *pre = "123##45##67###8##";
    /*char *pre = "12#4##3##";*/
    bt = btree_init(pre);
    count = 0;
    btree_preorder_traverse(bt, print);
    printf("\n%d\n", count);
    count = 0;
    printf(" The # of nodes that have one external node and one "
           "internal node: %d\n", btree_special_node_cnt(bt));
    printf("%d\n", count);
    btree_finalize(&bt);
    return 0;
}

void print(link_t l)
{
    if (l == NULL) {
        return ;
    }

    printf("%d ", l->item);
}
