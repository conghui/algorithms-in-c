#include <stdio.h>
int _bsearch(int *A, int a, int b, int n);
int bsearch(int *A, int size, int n);

#define MAX 100

int main(void)
{
    int i;
    int A[MAX];
    int n = 301;

    for (i = 0; i < MAX; i++) {
        A[i] = i;
    }

    if (bsearch(A, MAX, n)) {
        printf("%d is in the array\n", n);
    } else {
        printf("%d is not in the array\n", n);
    }

    return 0;
}

int _bsearch(int *A, int a, int b, int n)
{
    int mid;

    if (a > b) {
        return 0;
    }

    mid = a + ((b - a) >> 1);

    if (A[mid] == n) {
        return 1;
    } else if (A[mid] < n) {
        return _bsearch(A, mid + 1, b, n);
    } else {
        return _bsearch(A, a, mid - 1, n);
    }
}

int bsearch(int *A, int size, int n)
{
    return _bsearch(A, 0, size - 1, n);
}
