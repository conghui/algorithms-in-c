#include <stdio.h>
void bprint(unsigned int n);

int main(void)
{
    int i;

    for (i = 0; i <= 10; i++) {
        bprint(i);
        putchar('\n');
    }

    return 0;
}
void bprint(unsigned int n)
{
    if (n == 0) {
        putchar('0');
        return ;
    } else if (n == 1) {
        putchar('1');
        return;
    }

    bprint(n / 2);

    if ((n & 1) == 1) {
        putchar('1');
    } else {
        putchar('0');
    }
}
