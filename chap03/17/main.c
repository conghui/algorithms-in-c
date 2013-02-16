#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX 1000

int main(void)
{
    int A[MAX];
    int i;
    int num;
    int size;
    int r;
    memset(A, 0, MAX * sizeof *A);

    for (i = 0; i < MAX; i++) {
        if ((r = scanf("%d", &num)) == 1) {
            A[num]++;
        } else {
            break;
        }
    }

    if (r == EOF) {
        size = i;
    } else {
        fprintf(stderr, "read error\n");
        exit(EXIT_FAILURE);
    }

    printf("%10s%10s\n", "n", "count");

    for (i = 0; i < size; i++) {
        printf("%10d%10d\n", i, A[i]);
    }

    return 0;
}
