#include <stdio.h>
void ruler(int a, int b, int h);
void mark(int h);

int main(void)
{
    ruler(0, 11, 4);
    mark(30);
    ruler(4, 20, 4);
    return 0;
}

void ruler(int a, int b, int h)
{
    int mid;

    if (a == b) {
        return ;
    }

    mid = a + ((b - a) >> 1);
    ruler(a, mid, h - 1);
    printf("%2d|", mid);
    mark(h);
    ruler(mid + 1, b, h - 1);
}

void mark(int h)
{
    while (h-- > 0) {
        putchar('-');
    }

    putchar('\n');
}

