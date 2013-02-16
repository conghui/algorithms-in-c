#include <stdio.h>
#include <math.h>
size_t getN(size_t n);

int main(void)
{
    size_t i   = 10;
    size_t max = 100000;

    for (; i <= max; i *= 10) {
        printf("For N = %7u, binary search becomes %6u times faster than sequential search\n",
               getN(i), i);
    }

    return 0;
}

size_t getN(size_t n)
{
    size_t i;

    for (i = 1; ; i++) {
        if ((i*0.5 < n *log2(i)) && ((i+1)*0.5 > n*log2(i+1))) {
            return i;
        }
    }

    return 0;
}
