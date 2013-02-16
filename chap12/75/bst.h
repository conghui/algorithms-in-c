#ifndef BST_H

#define BST_H

#define T bst_t

typedef struct _T *T;

T bst_init();
void bst_finalize(T *t);
void bst_insert(T t, int key);
void bst_sort(T t);
int bst_select(T t, int k);
void bst_partition(T t, int k);
void bst_delete(T t, int key);
int bst_empty(T t);
void bst_join(T t1, T t2);

#undef T

#endif /* end of include guard: BST_H */
