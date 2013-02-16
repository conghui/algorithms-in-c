#include <math.h>
#include <stdio.h>

static int n = 10;
static double lg(int n);
static unsigned long factorial(int n);

int main(void)
{
    printf("log(%d!)=%g\n", n, lg(n));
    printf("log(%d!)=%g\n", n, log10(factorial(n)));
    return 0;
}

static double lg(int n)
{
    if (n == 1) {
        return 0;
    }

    return log10(n) + lg(n - 1);
}

static unsigned long factorial(int n)
{
    if (n == 0) {
        return 1;
    }

    return n * factorial(n - 1);
}
