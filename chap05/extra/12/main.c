#include <stdio.h>
int mul(int a, int b);

int main(void)
{
    printf("4 * 3 = %d\n", mul(4, 3));
    return 0;
}

int mul(int a, int b)
{
    if (b == 1) {
        return a;
    }

    return mul(a, b - 1) + a;
}
