#include <stdio.h>
int subset_sum(int *A, int n, int goal);
int _subset_sum(int *A, int a, int b, int end, int *sum, int goal);

int main(void)
{
    int A[] = {1, 2, 3, 4, 5, 6, 7};
    int sum = 10;

    if (subset_sum(A, 7, sum)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}

int subset_sum(int *A, int n, int goal)
{
    int sum = 0;
    return _subset_sum(A, 0, 0, n - 1, &sum, goal);
}

int _subset_sum(int *A, int a, int b, int end, int *sum, int goal)
{
    if (b > end) {
        return 0;
    }

    *sum += A[b];

    if (*sum == goal) {
        return 1;
    }

    return _subset_sum(A, a, b + 1, end, sum, goal);
}
