#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"


int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        if (isspace(c) && c != '\n') {
            continue;
        }

        switch (c) {
            case '(':
                break;

            case ')':
                putchar(stack_pop());
                putchar(' ');
                break;

            case '+':
            case '*':
                stack_push(c);
                break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                putchar(c);
                putchar(' ');
                break;

            case '\n':
                putchar(c);
                break;

            default:
                fprintf(stderr, "unrecognize character %c\n", c);
                exit(EXIT_FAILURE);
                break;
        }
    }

    return 0;
}
