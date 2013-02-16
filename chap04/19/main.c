#include <stdio.h>

#include "stackArray.h"
#include "stackList.h"

int main(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        stackArray_push(i);
        stackList_push(i);
    }

    for (i = 0; i < 5; i++) {
        stackArray_pop();
        stackList_pop();
    }

    printf("stackArray count: %d\n", stackArray_count());
    printf("stackList count: %d\n", stackList_count());

    /* release the memory */
    while (!stackList_empty()) {
        stackList_pop();
    }

    return 0;
}
