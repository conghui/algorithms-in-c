#include "list.h"

int main(void)
{
    int i;
    node_t h;
    link head  = &h;
    head->next = NULL;

    for (i = 10; i >= 1; i--) {
        link newnode = listNew(i);
        listInsert(head, newnode);
    }

    printf("before rearrange: ");
    listPrint(head);
    listResort(head);
    printf("after rearrange:  ");
    listPrint(head);
    return 0;
}
