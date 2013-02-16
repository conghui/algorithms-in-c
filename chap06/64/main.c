#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "list.h"
void test();

int main(void)
{
    for (int i = 0; i < 2; i++)  {
        test();
    }

    return 0;
}

void test()
{
    list_t list = list_init();

    for (int i = 0; i < 20; i++) {
        list_append(list, rand() % 100);
    }

    list_show(list);
    list_sort(list);
    list_show(list);
    putchar('\n');
    list_finalize(&list);
}
