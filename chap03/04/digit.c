#include <math.h>
#include "digit.h"

void mean_stddev_i(int r, int n, double *mean, double *stddev)
{
    int x;
    int i;
    double var = 0.0;
    *stddev = *mean = 0.0;

    for (i = 0; i < n; i++) {
        x = m_rand_i(r);
        *mean += (double)x / n;
        var += (double)x*x / n;
    }

    *stddev = sqrt(var - pow(*mean, 2));
}

void mean_stddev_d(int r, int n, double *mean, double *stddev)
{
    int x;
    int i;
    double var = 0.0;
    *stddev = *mean = 0.0;

    for (i = 0; i < n; i++) {
        x = m_rand_d() * r;
        *mean += (double)x / n;
        var += (double)x*x / n;
    }

    *stddev = sqrt(var - pow(*mean, 2));
}
