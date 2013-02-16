#include <stdio.h>

int main(void)
{
    return 0;
}

#define bitsbyte CHAR_BIT
#define bitsword (CHAR_BIT * sizeof(int))
#define bytesword (sizeof(int))
#define R (1 << bitsbyte)

#define digit(A, B) \
    ((A) >> (bitsword - ((B)+1)*bitsbyte)) & (R-1)


