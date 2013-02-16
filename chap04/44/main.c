#include <stdio.h>

#include "randlist.h"

int main(void)
{
    int n = 5;
    int i;

    for (i = 1; i <= 99; i++) {
        randlist_push(i);
    }

    while (n-- > 0) {
        fprintf(stderr, "%d ", randlist_pop());
    }

    putchar('\n');
    return 0;
}
