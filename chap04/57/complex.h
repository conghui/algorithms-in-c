#ifndef COMPLEX_H

#define COMPLEX_H

#define T complex_t
typedef struct T *T;

T complex_init(double r, double i);
double complex_real(T t);
double complex_image(T t);
T complex_multi(T a, T b);
T complex_add(T a, T b);

#undef T

#endif /* end of include guard: COMPLEX_H */
