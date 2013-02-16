#include <stdio.h>

#define N 30

int main(void)
{
    char a[N];
    unsigned  i;
    unsigned j;

    for (i = 0; i < N; i++) {
        a[i] = 1;
    }

    for (i = 2; i < N; i++) {
        if (a[i] == 1) {
            for (j = i; i*j < N; j++) {
                a[i*j] = 0;
            }
        }
    }

    for (i = 2; i < N; i++) {
        if (a[i]) {
            printf("%d ", i);
        }
    }

    return 0;
}
