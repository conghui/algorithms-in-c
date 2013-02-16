#include "list.h"

int main(void)
{
    list_t head;
    head = list_new();
    int i;

    for (i = 0; i < 10; i++) {
        list_t nn = list_newnode(i);
        list_insert(head, nn);
    }

    list_for(head, node_print);
    /*list_reverse(head);*/
    /*list_for(head, node_print);*/
    list_sort(head);
    list_for(head, node_print);
    list_free(head);
    return 0;
}
