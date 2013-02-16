#include <math.h>
#include <stdio.h>
int findmax(int *A, int a, int b);

int main(void)
{
    int A[] = {1, 2 , 3 , 4 , 5, 6, 7, 8, 9, 10, 11};
    printf("The max value is %d\n", findmax(A, 0, 10));
    return 0;
}

int findmax(int *A, int a, int b)
{
    if (a == b) {
        return A[a];
    }

    int lmax; /* max of left portion */
    int rmax; /* max of right portion */
    int alast; /* last index of left portion */
    alast = a + pow(2, ceil(log2(b - a + 1)) - 1) - 1;
    lmax  = findmax(A, a, alast);
    rmax  = findmax(A, alast + 1, b);
    return lmax > rmax ? lmax : rmax;
}
