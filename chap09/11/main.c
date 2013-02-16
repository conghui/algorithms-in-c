#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "pq.h"

int main(void)
{
    int n = 30000;
    int max = 1000000;
    int times = 10;
    PQ_t pq = PQ_init(n);
    int i;

    for (i = 0; i < n; i++) {
        PQ_insert(pq, rand() % max);
    }

    int j;

    for (j = 0; j < times; j++) {
        clock_t begin = clock();

        for (i = 0; i < n/2; i++) {
            PQ_delmax(pq);
        }

        clock_t end = clock();
        printf("delete needs %.2f seconds\n",
               (double)(end - begin)/CLOCKS_PER_SEC);
        begin = clock();

        for (i = 0; i < n/2; i++) {
            PQ_insert(pq, rand() % max);
        }

        end = clock();
        printf("insert needs %.2f seconds\n",
               (double)(end - begin)/CLOCKS_PER_SEC);
    }

    PQ_finalize(&pq);
    return 0;
}
