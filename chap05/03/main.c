#include <stdio.h>
static int puzzle(int n);

#define MAX 1e6

int main(void)
{
    int i;

    for (i = 1; i <= MAX; i++) {
        puzzle(i);
        fprintf(stderr, "%d\n", i);
    }

    return 0;
}

static int puzzle(int n)
{
    if (n == 1) {
        return 1;
    }

    if ((n & 1) == 0) {
        return puzzle(n / 2);
    } else {
        return puzzle(n * 3 + 1);
    }
}
