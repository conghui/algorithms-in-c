#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "stack.h"

#define NUMBER '0'

int getop(char *buf);

int main(void)
{
    int c;
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

            case '\n':
                if (stack_count() == 1) {
                    printf("the result is: %d\n", stack_pop());
                } else {
                    fprintf(stderr, "invalid expression\n");
                    exit(EXIT_FAILURE);
                }

                break;

            default:
                fprintf(stderr, "unrecognize character %x\n", c);
                exit(EXIT_FAILURE);
        }
    }

    stack_free();
    return 0;
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
