#include <stdio.h>
#include "digit.h"

#define SIZE(X) \
    ((sizeof X) / (sizeof *X))

int main(void)
{
    size_t i;
    size_t j;
    double mean1, mean2;
    double stddev1, stddev2;
    int r[] = {2, 4, 16};
    int N[] = {1000, 10000, 100000, 1000000};
    printf("%s\t%s\t%s\t\t%s\t\t\t\t%s\t\t%s\n", "r", "N", "mean1", "stddev1",
           "mean2", "stddev2");

    for (i = 0; i < SIZE(r); i++) {
        for (j = 0; j < SIZE(N); j++) {
            mean_stddev_i(r[i], N[j], &mean1, &stddev1);
            mean_stddev_d(r[i], N[j], &mean2, &stddev2);
            printf("%d\t%d\t%f\t%f\t\t\t%f\t%f\n", r[i], N[j], mean1, stddev1,
                   mean2, stddev2);
        }
    }

    return 0;
}
