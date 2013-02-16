#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER '0'
static int postfix_cur(char *expr);
static int postfix_cur2(char *expr);
static int eval2(char *begin, char **end);
static int eval(char *expr, int *v1, int *v2);
static int getop(char **expr, int *n);

int main(void)
{
    char buf[BUFSIZ];

    while (fgets(buf, BUFSIZ, stdin)) {
        printf("%d\n", postfix_cur2(buf));
    }

    return 0;
}

static int postfix_cur(char *expr)
{
    int v1 = 0;
    int v2 = 0;
    return eval(expr, &v1, &v2);
}

static int postfix_cur2(char *expr)
{
    char *begin = expr;
    char *end   = begin + strlen(begin) - 1;
    return eval2(begin, &end);
}

static int eval2(char *begin, char **end)
{
    int n = 0;

    if (*end < begin) {
        printf("Hello\n");
        return n;
    }

    while (*end >= begin && isspace(**end)) {
        (*end)--;
    }

    if (**end == '+') {
        (*end)--;
        return eval2(begin, end) + eval2(begin, end);
    } else if (**end == '*') {
        (*end)--;
        return eval2(begin, end) * eval2(begin, end);
    } else if (isdigit(**end)) {
        n = **end - '0';
        (*end)--;

        while (isdigit((**end)) && (*end) >= begin) {
            n = n * 10 + **end - '0';
            (*end)--;
        }
    }

    return n;
}

static int eval(char *expr, int *v1, int *v2)
{
    int c;
    int n;

    if (isdigit(c = getop(&expr, &n))) {
        if (*v1 == 0) {
            *v1 = n;
        } else if (*v2 == 0) {
            *v2 = n;
        }

        eval(expr, v1, v2);
    } else if (c == '+') {
        *v1 += *v2;
        *v2  = 0;
        eval(expr, v1, v2);
    } else if (c == '*') {
        *v1 *= *v2;
        *v2  = 0;
        eval(expr, v1, v2);
    }

    return *v1;
}

static int getop(char **expr, int *n)
{
    char *cur = *expr;
    int result;

    while (isspace(*cur)) {
        cur++;
    }

    if (!isdigit(*cur)) {
        if (*cur != '\0') {
            int c = *cur;
            cur++;
            *expr = cur;
            return c;
        } else {
            return EOF;
        }
    }

    /* we get a digit */
    result = *cur - '0';

    while (isdigit(*++cur)) {
        result = result * 10 + *cur - '0';
    }

    *expr = cur;
    *n    = result;
    return NUMBER;
}
