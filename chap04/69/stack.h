#ifndef STACK_H

#define STACK_H

#include "complex.h"

#define T stack_t
typedef struct T *T;
T stack_init();
int stack_empty(T t);
void stack_push(T t, complex_t n);
complex_t stack_pop(T t);
void stack_finalize(T *t);

#undef T

#endif /* end of include guard: STACK_H */
