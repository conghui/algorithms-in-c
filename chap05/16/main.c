#include <stdio.h>
#include <stdlib.h>

int findmax(int *A, int a, int b);
void init(int *A, size_t n);
void print(int *A, size_t n);

int main(void)
{
    int A[10];
    init(A, 10);
    print(A, 10);
    printf("the max value is: %d\n", findmax(A, 0, 9));
    return 0;
}

int findmax(int *A, int a, int b)
{
    if (a == b) {
        return A[a];
    }

    int rmax; /* the remaining max value */
    rmax = findmax(A, a + 1, b);
    return A[a] > rmax ? A[a] : rmax;
}

void init(int *A, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++) {
        A[i] = rand() % 20;
    }
}

void print(int *A, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }

    putchar('\n');
}
