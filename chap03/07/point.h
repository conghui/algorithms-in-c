#ifndef POINT_H

#define POINT_H

typedef struct point_t {
    float x;
    float y;
} point_t;

float distance(const point_t *a, const point_t *b);
#endif /* end of include guard: POINT_H */
