#ifndef LIST_H

#define LIST_H

#define T list_t
#define item_t int

typedef struct node_t *link_t;
typedef struct _T *T;

T list_init(size_t n);
void list_finalize(T *t);
void list_push_back(T t, item_t item);
void list_print(T t);
void list_sort(T t);

#undef item_t
#undef T
#endif /* end of include guard: LIST_H */
