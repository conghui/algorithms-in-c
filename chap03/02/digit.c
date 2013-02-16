#include <stdlib.h>
#include <math.h>
#include "digit.h"

/**
 * @brief get a random number from 0 to (r-1)
 *
 * @param r given the max value
 *
 * @return  a rand number
 */
number_t myrand(number_t r)
{
    return rand() % r;
}

void avg_std(number_t r, int n, double *pavg, double *pstd)
{
    int i;
    number_t x;
    double sqr = 0.0;
    *pavg = 0.0;

    for (i = 0; i < n; i++) {
        x = myrand(r);
        *pavg += (double)x / n;
        sqr += (double)x*x / n;
    }

    *pstd = sqrt(sqr - *pavg * *pavg);
}
