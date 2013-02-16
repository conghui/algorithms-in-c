#include <stdio.h>

#include "queue.h"

int main(void)
{
    int i;
    queue_t q;
    q = queue_init();

    for (i = 0; i < 10; i++)  {
        queue_push(q, i);
    }

    while (!queue_empty(q)) {
        printf("%d ", queue_pop(q));
    }

    putchar('\n');
    queue_finalize(q);
    return 0;
}
