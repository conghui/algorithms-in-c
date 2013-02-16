#ifndef POINT_H

#define POINT_H

typedef struct point_t {
    float x;
    float y;
} point_t;

int on_line(const point_t *a, const point_t *b, const point_t *c);

#endif /* end of include guard: POINT_H */
