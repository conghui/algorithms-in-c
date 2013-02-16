#include <stdio.h>
#include <math.h>
int reverseDigit(int n);
int ndigit(int n);

int main(void)
{
    int n = 12345;
    printf("The reverse of %d is %d\n", n, reverseDigit(n));
    return 0;
}

int reverseDigit(int n)
{
    if (n / 10 == 0) {
        return n;
    }

    int last = n % 10;
    int ret = reverseDigit(n / 10);
    int fac = ndigit(n);
    ret     = last * (int)pow(10, fac - 1) + ret;
    return ret;
}

int ndigit(int n)
{
    int ret = 0;

    do {
        ret++;
        n /= 10;
    } while (n > 0);

    return ret;
}
