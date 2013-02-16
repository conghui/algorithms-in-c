#include <stdio.h>

#include "queue.h"

int main(void)
{
    int i;
    queue_init();

    for (i = 0; i < 10; i++) {
        queue_push(i);
    }

    for (i = 0; i < 5; i++) {
        printf("%d ", queue_pop());
        queue_push(i + 10);
    }

    putchar('\n');

    for (i = 0; i < 5; i++) {
        printf("%d ", queue_pop());
    }

    putchar('\n');

    while (!queue_empty()) {
        printf("%d ", queue_pop());
    }

    putchar('\n');
    return 0;
}
