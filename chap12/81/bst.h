#ifndef BST_H

#define BST_H

#define T bst_t

typedef struct T *T;

T bst_init();
void bst_finalize(T *t);
void bst_insert(T t, int key);
void bst_delete(T t, int key);
int bst_select(T t, int k);
void bst_join(T t1, T t2);
int bst_height(T t);
#undef T

#endif /* end of include guard: BST_H */
