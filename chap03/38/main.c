#include <stdio.h>
#include "list.h"

int main(void)
{
    int i;
    link head1 = new_list();
    link head2 = new_list();

    for (i = 0; i < 10; i++) {
        link nn = new_node(i); /* new node */
        list_insert(head1, nn);
    }

    list_print(head1);
    list_copy(head2, head1);
    list_print(head2);
    list_free(head1);
    list_free(head2);
    return 0;
}
