#include <string.h>
#include <stdio.h>
static int _ispalindrome(char *A, int a, int b);
int ispalindrome(char a[], int n);

int main(void)
{
    char *str = "12323321";

    if (ispalindrome(str, strlen(str))) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}

int ispalindrome(char a[], int n)
{
    return _ispalindrome(a, 0, n - 1);
}

static int _ispalindrome(char *A, int a, int b)
{
    if (a >= b) {
        return 1;
    } else if (a == b - 1) {
        return A[a] == A[b];
    }

    if (A[a] != A[b]) {
        return 0;
    }

    return _ispalindrome(A, a + 1, b - 1);
}
