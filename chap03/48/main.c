#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    int i;
    list_t head;
    head = list_new();

    for (i = 30; i >= 1; i--) {
        list_t newnode = list_newnode(i);
        list_insert_next(head, newnode);
    }

    /* print and delete the element that can be divided by 5 */
    list_t prev = head;
    list_t cur  = prev->next;
    printf("Nodes to be delete: ");

    for (i = 1; cur != NULL; i++) {
        if (i % 5 == 0) {
            list_t tmp = cur;
            prev->next = cur->next;
            cur        = cur->next;
            printf("%d ", tmp->entry);
            free(tmp);
        } else {
            prev = cur;
            cur  = cur->next;
        }
    }

    putchar('\n');
    printf("The remaining nodes: ");
    list_for(head, node_print);
    list_delete(head);
    return 0;
}
