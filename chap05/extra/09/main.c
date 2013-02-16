#include <stdio.h>
void letter(int c);

int main(void)
{
    letter('D');
    return 0;
}

void letter(int c)
{
    if (c == 'A') {
        putchar(c);
        return;
    }

    letter(c - 1);
    printf("%c", c);
    letter(c - 1);
}
