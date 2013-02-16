#include <stdio.h>

#include "queue.h"

int main(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        queue_push(i);
    }

    while (!queue_empty()) {
        printf("%d ", queue_pop());
    }

    putchar('\n');
    return 0;
}
