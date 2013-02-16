#include <math.h>
#include "triangle.h"

float area_triangle(const triangle_t *t)
{
    float ab = dist(&t->a, &t->b);
    float bc = dist(&t->b, &t->c);
    float ac = dist(&t->a, &t->c);
    float halfcir = (ab+bc+ac) / 2;
    return sqrt(halfcir * (halfcir-ab) * (halfcir-bc) * (halfcir-ac));
}
