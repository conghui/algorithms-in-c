#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

#define nil '\0'
#define NUMBER '0'
static void pop_param(char *buf, int need_param);
static int getop(char *store);
static int precedence(int o);
static int opgt(int a, int b);

int main(void)
{
    int c;
    char buf[BUFSIZ];
    char expr[BUFSIZ];
    char op1[BUFSIZ];
    char op2[BUFSIZ];
    int prevop     = 0;
    int need_param = 0;

    while ((c  = getop(buf)) != EOF) {
        switch (c) {
            case NUMBER:
                stack_push(buf);
                break;

            case '*':
            case '-':
            case '/':
            case '+':
                need_param = opgt(c, prevop);
                pop_param(op2, need_param);
                pop_param(op1, need_param);
                sprintf(expr, "%s%c%s", op1, c, op2);
                stack_push(expr);
                prevop = c;
                break;

            case '\n':
                stack_pop(expr);
                puts(expr);
                break;

            default:
                error("unrecognize character");
                break;
        }
    }

    return 0;
}

static void pop_param(char *buf, int need_param)
{
    char *last = buf;
    int has_op;
    stack_pop(buf);
    stack_push(buf);
    has_op = strpbrk(buf, "+-*/") == NULL ? 0 : 1;

    if (need_param && has_op) {
        *last++ = '(';
    }

    stack_pop(last);
    last += strlen(last);

    if (need_param && has_op) {
        *last++ = ')';
    }

    *last = nil;
}

/* only get unsigned int  type and operator,
 * not including the floating point digit and the nagetive operand*/
static int getop(char *store)
{
    int c;

    /* skip the white space */
    while (isspace(*store = c = getchar()) && c != '\n')
        ;

    store[1] = nil;

    if (!isdigit(c)) {
        return c;
    }

    /* c is digit */
    while (isdigit(c = getchar())) {
        *++store = c;
    }

    if (c != EOF) {
        ungetc(c, stdin);
    }

    *++store = nil;
    return NUMBER;
}

static int precedence(int o)
{
    if (o == '*' || o == '/') {
        return 2;
    } else if (o == '+' || o == '-') {
        return 1;
    }

    return 0;
}

static int opgt(int a, int b)
{
    /* b is empty */
    if (b == 0) {
        return 0;
    }

    if (precedence(a) > precedence(b)) {
        return 1;
    } else {
        return 0;
    }
}

