#include <stdio.h>

double power(double base, int exp)
{
    if (exp == 1) {
        return base;
    }

    return power(base, exp - 1) * base;
}

int main(void)
{
    printf("2 ^ 4 = %.2f\n", power(2, 4));
    return 0;
}
