#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

#define NTRI    10000 /* # of triangle */

#define m_rand_d() \
    ((double)rand() / RAND_MAX)

static point_t getpoint();
static triangle_t gettriangle();

int main(void)
{
    int i;
    triangle_t t;
    double area = 0.0;

    for (i = 0; i < NTRI; i++) {
        t = gettriangle();
        area += area_triangle(&t);
    }

    printf("avg area is: %f\n", area / NTRI);
    return 0;
}

static point_t getpoint()
{
    point_t p;
    p.x = m_rand_d();
    p.y = m_rand_d();
    return p;
}

static triangle_t gettriangle()
{
    triangle_t t;
    t.a = getpoint();
    t.b = getpoint();
    t.c = getpoint();
    return t;
}
