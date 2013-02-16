#include <stdlib.h>
#include <stdio.h>

#include "pq.h"

int main(void)
{
    int n = 100;
    PQ_t pq = PQ_init(n);
    int i;

    for (i = 0; i < 20; i++) {
        PQ_insert(pq, rand() % 100);
    }

    while (!PQ_empty(pq)) {
        printf("%3d ", PQ_delmax(pq));
    }

    putchar('\n');
    PQ_finalize(&pq);
    return 0;
}
