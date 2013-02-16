#ifndef PQ_H

#define PQ_H

#define T PQ_t
#define item_t int

typedef struct _T *T;

T PQ_init(size_t n);
void PQ_finalize(T *t);
int PQ_empty(T t);
void PQ_insert(T t, item_t item);
item_t PQ_delmax(T t);

#undef T
#undef item_t

#endif /* end of include guard: PQ_H */
