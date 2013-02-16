#include <stdlib.h>
#include <stdio.h>

#include "list.h"

#define SIZE(x) \
    ((sizeof x) / (sizeof *x))

#define M 2

int main(void)
{
    int i;
    list_t head;
    list_t tail;
    int N[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};
    unsigned int j;

    for (j = 0; j < SIZE(N); j++) {
        tail = head = list_init(N[j]);

        for (i = 1; i <= N[j]; i++) {
            list_t nn = list_newnode(i);
            list_insert_next(tail, nn);
            tail  = nn;
        }

        list_t cur = head->next;

        while (cur != cur->next) {
            for (i = 1; i < M - 1; i++) {
                cur = cur->next;
            }

            list_t tmp = list_delete_next(cur);
            cur        = tmp->next;
            /*printf("%d ", tmp->entry);*/
            list_free_node(tmp);
        }

        head->next = cur;
        /*list_print(head);*/
        list_delete(head);
    }

    return 0;
}
