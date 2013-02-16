#include <stdio.h>

#include "digit.h"

#define SIZE(x) \
    ((sizeof(x)) / (sizeof *x))

int main(void)
{
    size_t i;
    size_t j;
    double mean;
    double stddev;
    int R[] = {10, 100, 1000};
    int N[] = {1000, 10000, 100000, 1000000};
    printf("%s\t%s\t%s\t\t%s\n", "r", "n", "mean", "std.dev");

    for (i = 0; i < SIZE(R); i++) {
        for (j = 0; j < SIZE(N); j++) {
            mean_stddev(R[i], N[j], &mean, &stddev);
            printf("%d\t%d\t%f\t%f\n", R[i], N[j],mean, stddev);
        }
    }

    return 0;
}
