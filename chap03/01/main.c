#include <limits.h>
#include <float.h>
#include <stdio.h>

int main(void)
{
    printf("%8s%15d - %15d\n", "int: ", INT_MIN, INT_MAX);
    printf("%8s%15ld - %15ld\n", "long: ", LONG_MIN, LONG_MAX);
    printf("%8s%15hd - %15hd\n", "short: ", SHRT_MIN, SHRT_MAX);
    printf("%8s%15g - %15g\n", "float: ", FLT_MIN, FLT_MAX);
    printf("%8s%15g - %15g\n", "double: ", DBL_MIN, DBL_MAX);
    return 0;
}
