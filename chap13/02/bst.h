#ifndef BST_H

#define BST_H

#define T bst_t

typedef struct T *T;

T bst_init();
void bst_finalize(T *t);
void bst_insert_normal(T t, int item);
void bst_insert_balance(T t, int item);
int bst_find(T t, int item);
#undef T

#endif /* end of include guard: BST_H */
