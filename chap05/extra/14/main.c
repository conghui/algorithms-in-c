#include <stdio.h>

double harmonicSum(int n)
{
    if (n == 1) {
        return 1;
    }

    return harmonicSum(n - 1) + 1.0 / n;
}

int main(void)
{
    printf("1 + 1/2 + 1/3 + 1/4 = %f\n", harmonicSum(4));
    return 0;
}
