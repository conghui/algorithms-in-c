#include <stdio.h>
#include <stdlib.h>
#include "link.h"

int main(void)
{
    int i;
    list_t head;
    list_t tail;
    head = list_new();
    tail = head;

    for (i = 1; i < 10; i++) {
        list_t newnode = list_new_node(i);
        list_insert_next(tail, newnode);
        tail = tail->next;
    }

    list_t cur = head->next;

    while (cur->next != cur) {
        for (i = 1; i < 4; i++) {
            cur = cur->next;
        }

        list_t tmp = cur->next;
        cur->next  = tmp->next;
        cur = cur->next;
        printf("%d ", tmp->entry);
        free(tmp);
    }

    /* one element left */
    head->next = cur;
    list_print(head);
    list_delete(head);
    return 0;
}
