#include <math.h>
#include "point.h"

float distance(const point_t *a, const point_t *b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return sqrt(dx*dx + dy*dy);
}
