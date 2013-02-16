#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
static void eval(char **expr);
static int getop(char **expr, int *n);

int main(void)
{
    char buf[BUFSIZ] = "(3 / ((1) * (1 + 2)))";
    char *p          = buf;
    eval(&p);
    return 0;
}

static void eval(char **expr)
{
    int c;
    int n;

    if ((c = getop(expr, &n)) == '(') {
        eval(expr);
        eval(expr);
    } else if (c == NUMBER) {
        printf("%d ", n);
    } else if (c == '+' || c == '*' || c == '/') {
        eval(expr);
        putchar(c);
        putchar(' ');
    }
}

static int getop(char **expr, int *n)
{
    char *p = *expr;
    int result;

    while (isspace(*p)) {
        p++;
    }

    if (!isdigit(*p)) {
        int c = *p;
        p++;
        *expr = p;
        return c;
    }

    result = *p - '0';

    while (isdigit(*++p)) {
        result = result * 10 + *p - '0';
    }

    *expr = p;
    *n    = result;
    return NUMBER;
}
