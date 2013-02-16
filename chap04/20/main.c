#include <stdio.h>

#include "stack.h"

int main(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        STACK_push(i);
    }

    return 0;
}
