#ifndef ST_H

#define ST_H

#define T st_t

typedef struct _T *T;
typedef int key_t;
typedef int bool;

#define false 0
#define true  1

T st_init(size_t capacity);
void st_finalize(T *t);
size_t st_size(T t);
bool st_search(T t, key_t k);
bool binary_search(key_t *a, int l, int r, key_t value);
void st_insert(T t, key_t k);
void st_sort(T t);
void st_delete(T t, key_t k);

#undef T

#endif /* end of include guard: ST_H */
