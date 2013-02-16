#ifndef STACK_H

#define STACK_H

#define T stack_t

typedef struct T *T;

T stack_init();
void stack_push(T t, int n);
int stack_pop(T t);
int stack_empty(T t);
void stack_finalize(T t);

#undef T

#endif /* end of include guard: STACK_H */
