#include <stdio.h>
int findmin(int A[], size_t n);

int main(void)
{
    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("The min value is: %d\n", findmin(A, 10));
    return 0;
}

int findmin(int A[], size_t n)
{
    if (n == 1) {
        return A[0];
    }

    int *mid;
    mid = A + (n >> 1);
    int ln = mid - A;
    int rn = n - ln;
    int lmin;
    int rmin;
    lmin = findmin(A, ln);
    rmin = findmin(mid, rn);
    return lmin < rmin ? lmin : rmin;
}
