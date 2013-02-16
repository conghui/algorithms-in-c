#include <stdio.h>

int sum(int n);

int main(void)
{
    printf("The sum of 1 to 100 is: %d\n", sum(100));
    return 0;
}

int sum(int n)
{
    if (n == 1) {
        return 1;
    }

    return n + sum(n - 1);
}
