#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "digit.h"

#define SIZE(x) \
    (sizeof(x)) / (sizeof(*x))

int main(void)
{
    int r[] = {10, 100, 1000};
    int n[] = {1000, 10000, 100000, 1000000};
    unsigned i;
    unsigned j;
    double avg;
    double std;
    srand(time(0));
    printf("%s\t%s\t%s\t%s\n", "r", "n", "avg", "std");

    for (i = 0; i < SIZE(r); i++) {
        for (j = 0; j < SIZE(n); j++) {
            avg_std(r[i], n[j], &avg, &std);
            printf("%d\t%d\t%g\t%g\n", r[i], n[j], avg, std);
        }
    }

    return 0;
}
