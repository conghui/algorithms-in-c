#ifndef POINT_H

#define POINT_H

#include <stdlib.h>

#define rand_float() \
    ((float)rand() / RAND_MAX)

typedef struct _point_t {
    float x;
    float y;
} point_t;

point_t getpoint();
float distpoint(const point_t *a, const point_t *b);

#endif /* end of include guard: POINT_H */
