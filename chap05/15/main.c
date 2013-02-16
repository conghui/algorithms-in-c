#include <stdio.h>
#include "list.h"
void revlist(list_t l);

int main(void)
{
    int i;
    list_t l;
    l = list_init();

    for (i = 1; i <= 9; i++) {
        list_push_back(l, i);
    }

    list_print(l);
    revlist(l);
    list_print(l);
    /*dellast(l);*/
    list_finalize(&l);
    return 0;
}

void revlist(list_t l)
{
    if (l->head->next == NULL) { /* only one item */
        return;
    }

    link first = l->head;
    l->head    = l->head->next;
    first->next   = NULL;
    revlist(l);
    link tmp;

    for (tmp = l->head; tmp->next != NULL; tmp = tmp->next) {
        ;
    }

    tmp->next = first;
}
