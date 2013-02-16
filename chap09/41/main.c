#include <stdio.h>
#include <stdlib.h>

#include "pq.h"

int main(void)
{
    int i;
    int n = 10;
    pq_t pq = pq_init();

    for (i = 0; i < n; i++) {
        pq_insert(pq,rand()%100);
    }

    pq_print(pq);
    pq_finalize(&pq);
    return 0;
}
