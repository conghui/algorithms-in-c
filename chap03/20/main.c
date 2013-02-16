#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int heads()
{
    return rand() < RAND_MAX / 6;
}

int main()
{
    int i;
    int j;
    int cnt;
    int N = 32;
    int M = 1000;
    int *f;
    f = malloc((N+1) * sizeof *f);
    assert(f);
    memset(f, 0, sizeof *f * (N+1));

    for (i = 0; i < M; i++, f[cnt]++) {
        for (cnt = 0, j = 0; j <= N; j++) {
            if (heads()) {
                cnt++;
            }
        }
    }

    for (j = 0; j <= N; j++) {
        printf("%2d ", j);

        for (i = 0; i < f[j]; i += 10) {
            putchar('*');
        }

        putchar('\n');
    }

    return 0;
}


