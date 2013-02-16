#include <stdio.h>

#include "pq.h"

int main(void)
{
    int i;
    int n = 10;
    pq_t pq = pq_init();
    pq_t pq2 = pq_init();

    for (i = 0; i < n; i++) {
        pq_insert(pq, n-i);
        pq_insert(pq2, 100+i);
    }

    pq_print(pq);
    pq_print(pq2);
    pq_join(pq, pq2);
    pq_print(pq);
    pq_t c = pq_copy(pq);
    pq_print(c);
    pq_finalize(&pq);
    pq_finalize(&pq2);
    pq_finalize(&c);
    return 0;
}
