#include <math.h>
#include "point.h"

point_t getpoint()
{
    point_t p;
    p.x = rand_float();
    p.y = rand_float();
    return p;
}

float distpoint(const point_t *a, const point_t *b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return sqrt(dx*dx + dy*dy);
}
