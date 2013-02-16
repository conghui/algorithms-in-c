#ifndef POINT_H

#define POINT_H

typedef struct _point_t {
    float x;
    float y;
} point_t;

float dist(const point_t *a, const point_t *b);
void printpoint(const point_t *p);
#endif /* end of include guard: POINT_H */
