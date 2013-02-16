#include <math.h>
#include <stdlib.h>
#include "point.h"

int on_line(
    const point_t *a,
    const point_t *b,
    const point_t *c)
{
    double k1 = (a->y - b->y) / (a->x - b->x);
    double k2 = (a->y - c->y) / (a->x - c->x);
    return fabs(k1 - k2) < pow(10, -4);
}
