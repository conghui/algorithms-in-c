#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define MAXSIZE 100

int main(void)
{
    int i;
    int n = 6;
    list_t list = list_init();

    for (i = 0; i < n; i++) {
        list_pushback(list, rand() % MAXSIZE);
    }

    list_print(list);
    list_sort(list);
    list_print(list);
    list_finalize(&list);
    return 0;
}
