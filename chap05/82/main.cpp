#include <stdio.h>

#include "btree.h"

void visit(link_t l);

int main(void)
{
    link_t tree = mytree();
    //preorder_traverse(tree, visit);putchar('\n');
    //preorder1(tree, visit); putchar('\n');
    //preorder2(tree, visit); putchar('\n');
    //preorder3(tree, visit); putchar('\n');
    //preorder4(tree, visit); putchar('\n');
    //inorder_traverse(tree, visit); putchar('\n');
    //inorder1(tree, visit); putchar('\n');
    //inorder2(tree, visit); putchar('\n');
    //inorder3(tree, visit); putchar('\n');
    postorder_traverse(tree, visit);
    putchar('\n');
    postorder1(tree, visit);
    putchar('\n');
    return 0;
}

void visit(link_t l)
{
    if (l == NULL) {
        return ;
    }

    printf("%c ", l->item);
}
