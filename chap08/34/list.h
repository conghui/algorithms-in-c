#ifndef LIST_H

#define LIST_H

#define T list_t
#define item_t int

typedef struct node *link_t;
typedef struct _T *T;

T list_init();
void list_finalize(T *t);
void list_pushback(T t, item_t item);
void list_sort(T t);
void list_print(T t);

#undef T
#undef item_t

#endif /* end of include guard: LIST_H */
