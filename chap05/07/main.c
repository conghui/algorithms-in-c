#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER '0'

static int eval();

static char a[BUFSIZ];
int main(void)
{
    fgets(a, BUFSIZ, stdin);

    if (a[strlen(a) - 1] == '\n') {
        a[strlen(a) - 1] = '\0';
    }

    printf("%d", eval());
    return 0;
}

int i = 0;
static int eval()
{
    int x = 0;

    while (a[i] == ' ') {
        i++;
    }

    if (a[i] == '+') {
        i++;
        return eval() + eval();
    }

    if (a[i] == '*') {
        i++;
        return eval() * eval();
    }

    while (isdigit(a[i])) {
        x = 10 * x + a[i] - '0';
        i++;
    }

    return x;
}
