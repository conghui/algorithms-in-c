#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "stack.h"

#define NUMBER '0'

static char buffer[BUFSIZ];
static char *next_char = buffer;

static void infix2postfix(char *s);
static int mygetchar();
static void myungetc(int c);
static int getop(char *s);
static int getop2(char *s);
static int issign(int c);

int main()
{
    double op2;
    char buf[BUFSIZ];
    int result;
    infix2postfix(buffer);
    puts(buffer);

    while ((result = getop2(buf) != EOF)) {
        switch (result) {
            case '+':
                STACK_push(STACK_pop() + STACK_pop());
                break;

            case '*':
                STACK_push(STACK_pop() * STACK_pop());
                break;

            case '/':
                op2 = STACK_pop();

                if (op2 == 0) {
                    error("zero divisor\n");
                }

                STACK_push(STACK_pop() / op2);
                break;

            case '-':
                op2 = STACK_pop();
                STACK_push(STACK_pop() / op2);
                break;

            case '$':
                STACK_push(sqrt(STACK_pop()));
                break;

            case NUMBER:
                STACK_push(atof(buf));
                break;

            case '\n':
                printf("%f\n", STACK_pop());
                break;

            default:
                error("unrecognize character %c\n", result);
                break;
        }
    }

    return 0;
}


static void infix2postfix(char *s)
{
    int c;
    char buf[BUFSIZ];

    while ((c = getop(buf)) != EOF) {
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '$':
                STACK_push(c);
                break;

            case NUMBER:
                strcat(s, buf);
                s += strlen(buf);
                c = atoi(buf);

                if (c < 0) {
                    STACK_push('-');
                }

                break;

            case '(':
                break;

            case ')':
                c = (int)STACK_pop();
                sprintf(s, "%c", c);
                s++;
                break;

            case '\n':
                sprintf(s, "%c", '\n');
                s++;
                break;

            default:
                error("unrecognized character\n");
        }
    }
}

static int mygetchar()
{
    if (next_char == buffer) {
        error("buffer is empty\n");
    }

    return *next_char++;
}

static void myungetc(int c)
{
    *--next_char = c;
}

static int getop(char *s)
{
    int c;

    /* skip the white space */
    while (isspace(c = *s = getchar()) && c != '\n')
        ;

    s[1] = '\0';

    if (!isdigit(c) && !issign(c) && c != '.') {
        return c;
    }

    /* scan the char after the sign */
    if (issign(c)) {
        if (isdigit(c = getchar())) {
            *++s = c;
        } else {
            ungetc(c, stdin);
            return *s;
        }
    }

    /* scan for the integral part */
    while (isdigit(c = getchar())) {
        *++s = c;
    }

    /* not a digit, is it a decimal point? */
    if (c == '.') {
        *++s = c;

        /* scan for the floating part */
        while (isdigit(c = getchar())) {
            *++s = c;
        }
    }

    if (c != EOF) {
        ungetc(c, stdin);
    }

    *++s = '\0';
    return NUMBER;
}
static int getop2(char *s)
{
    int c;

    /* skip the white space */
    while (isspace(c = *s = mygetchar()) && c != '\n')
        ;

    s[1] = '\0';

    if (!isdigit(c) && !issign(c) && c != '.') {
        return c;
    }

    /* scan the char after the sign */
    if (issign(c)) {
        if (isdigit(c = mygetchar())) {
            *++s = c;
        } else {
            myungetc(c);
            return *s;
        }
    }

    /* scan for the integral part */
    while (isdigit(c = mygetchar())) {
        *++s = c;
    }

    /* not a digit, is it a decimal point? */
    if (c == '.') {
        *++s = c;

        /* scan for the floating part */
        while (isdigit(c = mygetchar())) {
            *++s = c;
        }
    }

    if (c != EOF) {
        myungetc(c);
    }

    *++s = '\0';
    return NUMBER;
}

static int issign(int c)
{
    return c == '-' || c == '+';
}
