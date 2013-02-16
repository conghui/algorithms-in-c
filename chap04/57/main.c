#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

#define PI 3.1415926

int main(int argc, char **argv)
{
    int i;
    int j;
    int N;

    if (argc != 2) {
        fprintf(stderr, "usage: %s n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoi(argv[1]);
    complex_t t, x;
    printf("%dth complex roots of unity\n", N);

    for (i = 0; i < N; i++) {
        double r;
        r = 2.0 * PI * i / N;
        t = complex_init(cos(r), sin(r));
        printf("%2d (%6.3f + %6.3fi)^%d = ",
               i, complex_real(t), complex_image(t), N);

        for (x = t, j = 0; j < N - 1; j++) {
            x = complex_multi(t, x);
        }

        printf("%6.3f + %6.3fi\n", complex_real(x), complex_image(x));
    }

    return 0;
}
