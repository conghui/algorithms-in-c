#include <stdlib.h>
#include <math.h>

#include "digit.h"

double rand_d()
{
    return (double)rand() / RAND_MAX;
}

void mean_stddev(int r, int n, double *mean, double *stddev)
{
    int i;
    unsigned x;
    double var = 0.0;
    *mean = 0.0;

    for (i = 0; i < n; i++) {
        x = r * m_rand_d();
        *mean += (double)x / n;
        var += (double)x*x / n;
    }

    *stddev = sqrt(var - pow(*mean, 2.0));
}
