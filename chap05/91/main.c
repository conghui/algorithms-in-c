#include <stdio.h>

#include "btree.h"
void print(link_t l);

int main(void)
{
    btree_t bt;
    char *pre = "123##45##67###8##";
    /*char *pre = "12#4##3##";*/
    bt = btree_init(pre);
    btree_del_node(bt, 7);
    btree_del_node(bt, 5);
    btree_preorder_traverse(bt, print);
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
