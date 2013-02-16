#include <stdio.h>
#include "rbt.h"

#define SIZE(A) \
    (sizeof(A) / sizeof(*A))

int main(void)
{
    int A[] = {'A','S','E','R','C','H','I','N','G','X'};
    size_t i;
    rbt_t rbt = rbt_init();

    for (i = 0; i < SIZE(A); i++) {
        rbt_insert(rbt, A[i]);
    }

    return 0;
}
