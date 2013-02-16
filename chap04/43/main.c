#include <stdio.h>

#include "randlist.h"

int main(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        randlist_push(i);
    }

    while (!randlist_empty()) {
        fprintf(stderr, "%d ", randlist_pop());
    }

    putchar('\n');
    return 0;
}
