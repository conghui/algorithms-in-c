#include <stdlib.h>
#include <stdio.h>

#include "list.h"

#define N 10

int main(void)
{
    int i;
    list_t head;
    list_t tail;
    tail = head = list_init(100);

    for (i = 1; i <= N; i++) {
        list_t nn = list_newnode(i);
        list_insert_next(tail, nn);
        tail  = nn;
    }

    list_print(head);
    list_delete(head);
    return 0;
}
