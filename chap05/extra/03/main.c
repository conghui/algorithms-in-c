#include <stdio.h>
int recsum(int *A, int a, int b);
int findsum(int *A, size_t n);

static int times = 0;

int main(void)
{
    int i;
    int A[100];

    for (i = 0; i < 100; i++) {
        A[i] = i + 1;
    }

    printf("The sum of the array is: %d\n", findsum(A, 100));
    printf("Recursion times is: %d\n", times);
    return 0;
}

int recsum(int *A, int a, int b)
{
    times++;

    if (a == b) {
        return A[a];
    } else if (a == b - 1) {
        return A[a] + A[b];
    }

    int lsum = A[a];
    int rsum = recsum(A, a + 1, b);
    return lsum + rsum;
}

int findsum(int *A, size_t n)
{
    return recsum(A, 0, n - 1);
}
