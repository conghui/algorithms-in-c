#include <stdio.h>
static int gcd(int m, int n);

int main(void)
{
    gcd(5, 8);
    return 0;
}

static int i = 1;

static int gcd(int m, int n)
{
    printf("%d %*sgcd(%d,%d)\n", i, i, " ", m, n);
    i++;

    if (n == 0) {
        return m;
    }

    return gcd(n, m % n);
}
