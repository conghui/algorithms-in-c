#include <stdio.h>
//r represent ruler 
void r(int a, int b, int h);
//m represent mark
void m(int h);

int main(void)
{
    r(0, 11, 4);
    m(30);
    r(4, 20, 4);
    return 0;
}

void ruler(int a, int b, int h)
{
    int mid;

    if (a == b) {
        return ;
    }

    mid = a + ((b - a) >> 1);
    r(a, mid, h - 1);
    printf("%2d|", mid);
    m(h);
    r(mid + 1, b, h - 1);
}

void mark(int h)
{
    while (h-- > 0) {
        putchar('-');
    }

    putchar('\n');
}

