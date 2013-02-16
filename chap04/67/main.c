#include <stdio.h>

#include "stack.h"
static void test(stack_t s);

int main(void)
{
    int i;
    stack_t s;
    s = stack_init();

    for (i = 0; i < 2; i++) {
        test(s);
    }

    stack_finalize(s);
    return 0;
}

static void test(stack_t s)
{
    int i;

    for (i = 0; i < 10; i++) {
        stack_push(s, i);
    }

    while (!stack_empty(s)) {
        printf("%d ", stack_pop(s));
    }

    putchar('\n');
}
