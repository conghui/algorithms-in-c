#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "complex.h"
#include "stack.h"

#define nil '\0'
#define COMPLEX '0'

static int getop(complex_t *complex);

int main(void)
{
    complex_t complex;
    stack_t stack;
    stack = stack_init();
    int c;

    while ((c = getop(&complex)) != EOF) {
        switch (c) {
            case '+':
                stack_push(stack, complex_add(stack_pop(stack), stack_pop(stack)));
                break;

            case '*':
                stack_push(stack, complex_mult(stack_pop(stack), stack_pop(stack)));
                break;

            case COMPLEX:
                stack_push(stack, complex);
                break;

            case '\n':
                complex_print(stack_pop(stack));
                putchar('\n');
                break;

            default:
                printf("unknown character\n");
                exit(EXIT_FAILURE);
                break;
        }
    }

    stack_finalize(&stack);
    return 0;
}

static int getop(complex_t *complex)
{
    int c;
    double real  = 0;
    double image = 0;
    double sign = 1;

    /* skip the white space */
    while (isspace(c = getchar()) && c != '\n') {
        ;
    }

    if (!isdigit(c)) {
        return c;
    }

    /* we get a complex, first get the real part */
    real = c - '0';

    while (isdigit(c = getchar())) {
        real = real * 10 + c - '0';
    }

    /* we get the sign of image */
    sign = c == '-' ? -1 : 1;

    /* now we collext the image part */
    while (isdigit(c = getchar())) {
        image = image * 10 + c - '0';
    }

    if (c != 'i' && c != EOF) {
        ungetc(c, stdin);
    }

    image *= sign;
    *complex = complex_init(real, image);
    return COMPLEX;
}
