#ifndef DIGIT_H

#define DIGIT_H

#include <stdlib.h>

#define m_rand_i(x) \
    (rand() % x)

#define m_rand_d() \
    ((double)rand() / RAND_MAX)

void mean_stddev_i(int r, int n, double *mean, double *stddev);
void mean_stddev_d(int r, int n, double *mean, double *stddev);
#endif /* end of include guard: DIGIT_H */
