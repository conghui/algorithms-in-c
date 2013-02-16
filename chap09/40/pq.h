#ifndef PQ_H

#define PQ_H

#define T      pq_t
#define item_t int

typedef struct _T *T;

T pq_init();
void pq_finalize(T *_t);
int pq_empty(T t);
void pq_insert(T t, item_t item);
void pq_print(T t);
item_t pq_delete(T t, item_t key);
item_t pq_delmax(T t);
T pq_join(T t1, T t2);
T pq_copy(T t);

#undef item_t
#undef T

#endif /* end of include guard: PQ_H */
