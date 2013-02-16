#include <stdio.h>

#include "stack.h"

int main(void)
{
    int i = 0;

    while (!stack_full()) {
        stack1_push(i++);
        stack2_push(i++);
    }

    /* pop stack 1 */
    while (!stack1_empty()) {
        printf("%d ", stack1_pop());
    }

    putchar('\n');

    while (!stack2_empty()) {
        printf("%d ", stack2_pop());
    }

    putchar('\n');
    return 0;
}
