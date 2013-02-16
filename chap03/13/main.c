#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE(x) \
    ((sizeof x) / (sizeof *x))

int main(void)
{
    unsigned long long N[] = {1000ULL, 10000ULL, 100000ULL, 1000000ULL};
    unsigned i;
    unsigned long long j, k;
    int *a;

    for (i = 0; i < SIZE(N); i++) {
        a = malloc(N[i] * sizeof *a);
        assert(a);

        for (j = 0ULL; j < N[i]; j++) {
            a[j] = 1;
        };

        for (j = 2ULL; j < N[i]; j++) {
            if (a[j] == 1) {
                for (k = 2ULL; j*k < N[i]; k++) {
                    a[j*k] = 0;
                };
            }
        }

        for (j = 2ULL; j < N[i]; j++) {
            if (a[j]) {
                printf("%llu\n", j);
            }
        }

        printf("\n\n\n");
        free(a);
    }

    return 0;
}
