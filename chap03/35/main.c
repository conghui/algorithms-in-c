#include "node.h"

int main(void)
{
    int i;
    node_t h;
    link head = &h;
    head->next = NULL;

    for (i = 0; i < 10; i++) {
        link newnode = list_new_node(i);
        list_insert(head, newnode);
    }

    list_mv1st(head);
    list_print(head);
    list_free(head);
    return 0;
}
