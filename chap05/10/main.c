#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
static int eval(char **expr, int *v1);
static int getop(char **expr, int *n);

int main(void)
{
    char buf[BUFSIZ] = "(((1) + (2)) * 3)";
    char *p = buf;
    int v1  = 0;
    printf("%d\n", eval(&p, &v1));
    return 0;
}

static int eval(char **expr, int *v1)
{
    int c;
    int n;

    if ((c = getop(expr, &n)) == '(') {
        eval(expr, v1);
        eval(expr, v1);
    } else if (c == ')') {
        return *v1;
    } else if (c == NUMBER) {
        *v1 = n;
        eval(expr, v1);
    } else if (c == '+') {
        int n = *v1;
        *v1 = n + eval(expr, v1);
    } else if (c == '*') {
        int n = *v1;
        *v1 = n * eval(expr, v1);
    }

    return *v1;
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
