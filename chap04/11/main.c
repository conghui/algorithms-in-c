#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#include "stack.h"

#define NUMBER '0'

void infix2postfix();
void cal_post_expr();
void error(const char *fmt, ...);
int getop(char *buf);

int main(void)
{
    infix2postfix();
    return 0;
}

void infix2postfix()
{
    int c;
    char buf[BUFSIZ];
    stack_init(BUFSIZ);

    while ((c = getop(buf)) != EOF) {
        switch (c) {
            case NUMBER:
                printf("%s ", buf);
                break;

            case '(':
                break;

            case '*':
            case '+':
            case '-':
            case '/':
                stack_push(c);
                break;

            case ')':
                printf("%c ", stack_pop());
                break;

            case '\n':
                putchar(c);
                break;

            default:
                error("unrecognized character %c\n", c);
                break;
        }
    }
}

void cal_post_expr()
{
    int c;
    int op2;
    char buf[BUFSIZ];
    stack_init(BUFSIZ);

    while ((c = getop(buf)) != EOF) {
        switch (c) {
            case NUMBER:
                stack_push(atoi(buf));
                break;

            case '+':
                stack_push(stack_pop() + stack_pop());
                break;

            case '*':
                stack_push(stack_pop() * stack_pop());
                break;

            case '-':
                op2 = stack_pop();
                stack_push(stack_pop() - op2);
                break;

            case '/':
                op2 = stack_pop();

                if (op2 == 0) {
                    error("zero divisor\n");
                }

                stack_push(stack_pop() / op2);
                break;

            case '\n':
                if (stack_count() == 1) {
                    printf("the result is: %d\n", stack_pop());
                } else {
                    error("invalid expression\n");
                }

                break;

            default:
                error("unrecognize character %x\n", c);
        }
    }

    stack_free();
}

void error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    exit(EXIT_FAILURE);
    va_end(ap);
}

/**
 * @brief get operator or operation (int) from stdin and store it into buf
 *
 * @param buf containing the result
 *
 * @return indicator
 */
int getop(char *buf)
{
    int c;

    /* skip the space */
    while (isspace(*buf = c = getchar()) && c != '\n') {
        ;
    }

    buf[1] = '\0';

    if (!isdigit(*buf)) { /* not a digit */
        return *buf;
    }

    /* is a digit */
    while (isdigit(*++buf = c = getchar())) {
        ;
    }

    /* not a digit */
    if (c != EOF) {
        ungetc(c, stdin);
    }

    *buf = '\0';
    return NUMBER;
}
