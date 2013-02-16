#include <stdio.h>
#include "node.h"

int main(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        list_add(i);
    }

    printf("%d\n", list_size());
    list_free();
    return 0;
}
