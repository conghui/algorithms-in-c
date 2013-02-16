#include <stdio.h>

#include "list.h"
int findmax(link head);

int main()
{
    int i;
    list_t l;
    l = list_init();

    for (i = 10; i >= 0; i--) {
        list_insert_front(l, i);
    }

    list_print(l);
    printf("The max value is: %d\n", findmax(l->head));
    list_finalize(&l);
    return 0;
}

int findmax(link head)
{
    if (head->next == NULL) {
        return head->entry;
    }

    int rmax; /* remaining max */
    int cmax ; /* current max */
    cmax = head->entry;
    rmax = findmax(head->next);
    return cmax > rmax ? cmax : rmax;
}
