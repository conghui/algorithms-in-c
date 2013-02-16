#ifndef TRIANGLE_H

#define TRIANGLE_H

#include "point.h"

typedef struct _triangle_t {
    point_t a;
    point_t b;
    point_t c;
} triangle_t;

float area_triangle(const triangle_t *t);
#endif /* end of include guard: TRIANGLE_H */
