#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main(void)
{
    int i;
    node_t h;
    node_t *head = &h;
    head->next = NULL;

    for (i = 0; i < 10; i++) {
        node_t *newnode = newNode(i);
        listInsert(head, newnode);
    }

    mvB2last(head);
    printNode(head);
    freeList(head);
    return 0;
}
