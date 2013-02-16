#include <math.h>
#include <stdio.h>

#include "point.h"

float dist(const point_t *a, const point_t *b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return sqrt(dx*dx + dy*dy);
}

void printpoint(const point_t *p)
{
    printf("(%f, %f)\n", p->x, p->y);
}
