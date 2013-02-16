#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned char Bit;

#define m_rand_b() \
    (rand() % 2)

int main(int argc, const char *argv[])
{
    int i;
    double m1 = 0.0;
    double m2 = 0.0;

    if (argc == 1) {
        fprintf(stderr, "usage: %s n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(*++argv);

    for (i = 0; i < N; i++) {
        Bit b = m_rand_b();
        m1 = (double)b / N;
        m2 = (double)b*b / N;
    }

    printf("%10s: %f\n", "Avg", m1);
    printf("%10s: %f\n", "Stddev", sqrt(m2-m1*m2));
    return 0;
}
