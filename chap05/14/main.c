#include <stdio.h>
#include "list.h"
void dellast(list_t l);

int main(void)
{
    int i;
    list_t l;
    l = list_init();

    for (i = 1; i <= 9; i++) {
        list_push_back(l, i);
    }

    list_print(l);
    dellast(l);
    /*list_finalize(&l);*/
    return 0;
}

void dellast(list_t l)
{
    link cur;
    link prev;
    int i;

    if (l->head->next == l->head) {
        /* the last entry */
        printf("%d\n", l->head->entry);
        return;
    }

    cur = l->head;

    for (i = 0; i < 4; i++) {
        prev = cur;
        cur  = cur->next;
    }

    prev->next = cur->next;
    l->head = cur->next;
    printf("\t%d\n", cur->entry);
    dellink(&cur);

    if (cur == l->tail) {
        l->tail = prev;
    }

    dellast(l);
}
