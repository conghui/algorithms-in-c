#ifndef PQ_H

#define PQ_H

#define T      pq_t
#define item_t int

typedef struct _T *T;

T pq_init(size_t n);
void pq_finalize(T *t);
int pq_empty(T t);
void pq_insert(T t, item_t item);
item_t pq_delmax(T t);

#undef T
#undef item_t
#endif /* end of include guard: PQ_H */
