#include <math.h>
#include <stdio.h>

typedef double Item;

#define eq(A, B) \
    ((fabs((A) - (B))) / ((A) > (B) ? (A) : (B)) < 1e-6)

int main(void)
{
    double d1;
    double d2;
    d1 = 3.1415926;
    d2 = 3.1415927;

    if (eq(d1, d2)) {
        printf("%.10f equals to %.10f\n", d1, d2);
    }

    return 0;
}
