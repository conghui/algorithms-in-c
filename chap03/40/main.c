#include <stdio.h>
#include "list.h"

int main(void)
{
    int i;
    list_t head;
    head = list_new();

    for (i = 0; i < 10; i++) {
        list_t nn = list_newnode(i);
        list_insert(head, nn);
    }

    list_for(head, print);
    list_t evenhead = list_cp_if(head, is_even); /* remove the elements that has
                                                    even entry */
    list_for(head, print);
    list_for(evenhead, print);
    list_free(head);
    list_free(evenhead);
    return 0;
}
