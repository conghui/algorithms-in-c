#ifndef DIGIT_H

#define DIGIT_H

#include <stdlib.h>

#define m_rand_d() \
    ((double)rand() / RAND_MAX)

double rand_d();
void mean_stddev(int r, int n, double *mean, double *stddev);
#endif /* end of include guard: DIGIT_H */
