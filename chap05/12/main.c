#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER '0'
#define nil '\0'

static char *post2infix(char *expr, char *store);
static void eval(char **expr, char *v1, char *v2);
static int getop(char **expr, char *s);
int main(void)
{
    char buf[BUFSIZ] = "1 2 + 3 * 4 +";
    char store[BUFSIZ];
    printf("%s\n", post2infix(buf, store));
    return 0;
}

static char *post2infix(char *expr, char *store)
{
    static char buf[BUFSIZ];
    eval(&expr, store, buf);
    return store;
}

/* the method can only hold two variable v1 and v2,
 * if there are more than two variable, the function cannot work
 * well. Instead, you should implement it using a global stack.
 * */
static void eval(char **expr, char *v1, char *v2)
{
    int c;
    static char buf[BUFSIZ];
    static char result[BUFSIZ];
    static char *p = buf;

    if ((c = getop(expr, result)) == '+' || c == '*') {
        p  = buf;
        *p++ = '(';
        strcpy(p, v1);
        p += strlen(v1);
        *p++ = c;
        strcpy(p, v2);
        p += strlen(v2);
        *p++ = ')';
        *p = nil;
        strcpy(v1, buf);
        *v2 = nil;
        eval(expr, v1, v2);
    } else if (c == NUMBER) {
        if (*v1 == nil) {
            strcpy(v1, result);
        } else if (*v2 == nil) {
            strcpy(v2, result);
        }

        eval(expr, v1, v2);
    }
}

static int getop(char **expr, char *s)
{
    char *p = *expr;

    while (isspace(*p)) {
        p++;
    }

    s[0] = *p;
    s[1] = nil;

    if (!isdigit(s[0])) {
        p++;
        *expr = p;
        return s[0];
    }

    /* we would get a digit */
    while (isdigit(*++p)) {
        *++s = *p;
    }

    *++s = nil;
    *expr = p;
    return NUMBER;
}
