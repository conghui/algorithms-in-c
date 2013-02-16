#ifndef BST_H

#define BST_H

#include "globvar.h"
#include "type.h"

#define T bst_t

typedef struct _T *T;

T bst_init();
void bst_finalize(T *t);
size_t bst_size(T t);
void bst_insert(T t, item_t item);
item_t bst_search(T t, item_t item);
void bst_sort(T t, UnaryFunction2 f);
void bst_search_insert(T t, item_t item);

#undef T

#endif /* end of include guard: BST_H */
