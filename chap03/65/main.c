#include <stdio.h>
static int gcd(int a, int b);
static int gcd2(int a, int b);

int main(void)
{
    int i, j;
    /*int matrix[10][10] = {0};*/
    printf("   ");

    for (i = 0; i < 10; i++) {
        printf("%3d", i+1);
    }

    printf("\n");

    for (i = 0; i < 10; i++) {
        printf("%3d", i+1);

        for (j = 0; j < 10; j++) {
            printf("%3d", gcd(i+1, j+1));

            if (gcd(i+1, j+1) != gcd2(i+1, j+1)) {
                printf("Opps\n");
                break;
            }
        }

        printf("\n");
    }

    return 0;
}

static int gcd(int a, int b)
{
    if (a == b) {
        return a;
    } else if (a > b) {
        return gcd(a-b, b);
    } else {
        return gcd(a, b-a);
    }
}

static int gcd2(int a, int b)
{
    if (a == b) {
        return a;
    } else if (a > b) {
        return gcd2(b, a-b);
    } else {
        return gcd2(b-a, a);
    }
}
