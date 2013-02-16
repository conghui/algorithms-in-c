#ifndef RBT_H

#define RBT_H

#define T rbt_t

typedef int item_t;
typedef struct _T *T;

T rbt_init();
void rbt_insert(T t, item_t item);
#undef T

#endif /* end of include guard: RBT_H */
