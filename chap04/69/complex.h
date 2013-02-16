#ifndef COMPLEX_H

#define COMPLEX_H

#define T complex_t

typedef struct T *T;

T complex_init(double r, double i);
void complex_finalize(T *t);
double complex_real(T t);
double complex_image(T t);
T complex_add(T a, T b);
T complex_mult(T a, T b);
T complex_copy(T t);
void complex_print(T t);

#undef T

#endif /* end of include guard: COMPLEX_H */
