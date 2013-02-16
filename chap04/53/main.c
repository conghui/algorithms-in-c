#include <stdio.h>

#include "queue.h"
static void test();

int main(void)
{
    queue_init();
    test();
    queue_finalize();
    return 0;
}

static void test()
{
    int i;

    for (i = 0; i < 10; i++) {
        queue_push(i);
    }

    for (i = 0; i < 5; i++) {
        queue_push(i);
    }

    while (!queue_empty()) {
        printf("%d ", queue_pop());
    }

    putchar('\n');
}
