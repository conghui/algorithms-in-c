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
    pq_t c = pq_join(pq, pq2);
    pq_print(c);
    pq_finalize(&c);
    return 0;
}
