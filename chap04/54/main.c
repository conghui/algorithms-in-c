#include <stdio.h>

#include "queue.h"
static void test();

int main(void)
{
    int i;
    queue_init(100);

    for (i = 0; i < 2; i++) {
        test();
    }

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
        fprintf(stderr, "%d ", queue_pop());
    }

    putchar('\n');
}
