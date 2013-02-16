#include <stdio.h>
#include <assert.h>

static int gcd(int m, int n);
static int gcd2(int m, int n);

int main(void)
{
    int i;
    int j;

    for (i = 1; i < 100; i++) {
        for (j = 1; j < 100; j++) {
            assert(gcd(i, j) == gcd2(i, j));
        }
    }

    printf("OK\n");
    return 0;
}

static int gcd(int m, int n)
{
    if (n == 0) {
        return m;
    }

    return gcd(n, m % n);
}

static int gcd2(int m, int n)
{
    while (m % n != 0) {
        int tmp;
        tmp = m;
        m   = n;
        n   = tmp % m;
    }

    return n;
}
