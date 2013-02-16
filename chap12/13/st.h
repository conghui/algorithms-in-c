#ifndef ST_H

#define ST_H

#include <stddef.h>
#define T st_t

typedef int key_t;

typedef struct _T *T;

T st_init(size_t max);
void st_finalize(T *t);
void st_insert(T t, key_t k);
void st_delete(T t, key_t k);
int st_select(T t, int k);
double st_avg(T t);

#undef T

#endif /* end of include guard: ST_H */
