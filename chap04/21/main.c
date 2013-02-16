#include "stack.h"

int main(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        stack_push(i);
    }

    stack_print();
    stack_clear();
    stack_pop();
    return 0;
}
