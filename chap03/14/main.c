#include <stdio.h>

#define N   1000000

static int A[N];

static int primecnt(int n)
{
    int i;
    int j;
    int cnt;

    for (i = 0; i < n; i++) {
        A[i] = 1;
    }

    for (i = 2; i < n; i++) {
        if (A[i] == 1) {
            for (j = i; i*j < n; j++) {
                A[i*j] = 0;
            }
        }
    }

    for (cnt = 0, i = 2; i < n; i++) {
        cnt += A[i] == 1 ? 1 : 0;
    }

    return cnt;
}

int main(void)
{
    int max = 1001;
    int i;

    for (i = 100; i < max; i += 100) {
        int j;
        int cnt = primecnt(i);
        printf("%4d: ", i);

        for (j = 10; j <= cnt; j += 10) {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
