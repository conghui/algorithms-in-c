#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    int i;
    list_t head;
    list_t tail;
    tail = head = list_init();

    for (i = 1; i <= 10; i++) {
        list_t nn = list_newnode(i);
        list_insert_next(tail, nn);
        tail = nn;
    }

    /* print and delete the even element */
    printf("Delete the following elements: ");
    list_t prev = head;
    list_t cur  = prev->next;

    for (i = 1; cur != NULL; i++) {
        if (i % 2 == 0) { /* delete the cur node */
            list_t tmp = cur;
            prev->next = cur->next;
            cur        = cur->next;
            printf("%d ", tmp->entry);
            free(tmp);
        } else {
            prev       = cur;
            cur        = cur->next;
        }
    }

    putchar('\n');
    printf("The remaining elements: ");
    list_print(head);
    list_delete(head);
    return 0;
}
