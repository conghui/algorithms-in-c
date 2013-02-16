#include <stdio.h>

#include "stack.h"

int main(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        stack_push(i);
    }

    for (i = 0; i < 5; i++) {
        stack_push(i);
    }

    while (!stack_empty()) {
        printf("%d ", stack_pop());
    }

    putchar('\n');
    return 0;
}
