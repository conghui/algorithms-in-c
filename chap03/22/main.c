#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <stdlib.h>
#include "point.h"

typedef struct _pair_t {
    int ia;
    int ib;
} pair_t;

int main(int argc, const char *argv[])
{
    int i, j;

    if (argc != 2) {
        fprintf(stderr, "usage: %s N\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    point_t *parr = malloc(n * sizeof *parr);
    assert(parr);

    for (i = 0; i < n; i++) {
        parr[i] = getpoint();
    }

    pair_t mindistpair = {0, 0};
    float mindist = FLT_MAX;
    float dist;

    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            if ((dist = distpoint(parr+i, parr+j)) < mindist) {
                mindistpair.ia = i;
                mindistpair.ib = j;
                mindist = dist;
            }
        }
    }

    printf("the closest two point is: (%f, %f) and (%f, %f)\n",
           parr[mindistpair.ia].x, parr[mindistpair.ia].y,
           parr[mindistpair.ib].x, parr[mindistpair.ib].y);
    return 0;
}
