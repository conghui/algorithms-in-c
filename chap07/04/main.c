#include <stdio.h>

#include "list.h"

int main(void)
{
    int n = 5;
    list_t list;
    list = list_init(n);
    list_print(list);
    list_sort(list);
    list_print(list);
    list_finalize(&list);
    return 0;
}
