#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "point.h"

int main(void)
{
    int rt;
    float mindist;
    float dist;
    point_t inpoint;
    point_t fstpoint;
    point_t minpoint = {0.0, 0.0};

    if (scanf("%f%f", &fstpoint.x, &fstpoint.y) != 2) {
        fprintf(stderr, "please give a float pair as the first point\n");
        exit(EXIT_FAILURE);
    }

    mindist = FLT_MAX;

    while ((rt = scanf("%f%f", &inpoint.x, &inpoint.y)) == 2) {
        dist = distance(&fstpoint, &inpoint);

        if (dist < mindist) {
            mindist = dist;
            minpoint = inpoint;
        }
    }

    if (rt == EOF) {
        printf("the min distance is: %f, the point is (%f, %f)\n", mindist,
               minpoint.x, minpoint.y);
    } else {
        fprintf(stderr, "you should give a float pair\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
