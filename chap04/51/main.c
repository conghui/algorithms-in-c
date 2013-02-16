#include <stdio.h>

#include "stack.h"
static void test();

int main(void)
{
    int i;
    stack_init(10);

    for (i = 0; i < 2; i++) {
        test();
    }

    stack_final();
    return 0;
}

static void test()
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
}
