#include <stdio.h>
void pattern(int n, int i);
void printspace(int i);
void printstar(int n);

int main(void)
{
    pattern(8, 0);
    return 0;
}

void pattern(int n, int i)
{
    if (n == 1) {
        printspace(i);
        printf("*\n");
        return;
    }

    pattern(n / 2, i);
    printspace(i);
    printstar(n);
    putchar('\n');
    pattern(n / 2, i + n / 2);
}

void printspace(int i)
{
    while (i-- > 0) {
        printf("  ");
    }
}

void printstar(int n)
{
    while (n-- > 0) {
        printf("* ");
    }
}
