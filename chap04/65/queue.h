#ifndef QUEUE_H

#define QUEUE_H

#define T queue_t

typedef struct T *T;

T queue_init();
void queue_finalize(T t);
int queue_empty(T t);
void queue_push(T t, int n);
int queue_pop(T t);

#undef T

#endif /* end of include guard: QUEUE_H */
