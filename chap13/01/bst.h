#ifndef BST_H

#define BST_H

#define T bst_t

typedef struct T *T;

T bst_init();
void bst_finalize(T *t);
void bst_insert(T t, int item);
int bst_size(T t);
void bst_balance(T t);
void bst_sort(T t);

#undef T

#endif /* end of include guard: BST_H */
