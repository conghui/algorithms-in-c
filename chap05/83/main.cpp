#include <stdio.h>

#include "btree.h"

void visit(link_t l);

int main(void)
{
    link_t tree = mytree();
    inorder_traverse(tree, visit);
    putchar('\n');
    preorder_traverse(tree, visit);
    putchar('\n');
    postorder_traverse(tree, visit);
    return 0;
}

void visit(link_t l)
{
    if (l == NULL) {
        return ;
    }

    printf("%c ", l->item);
}
