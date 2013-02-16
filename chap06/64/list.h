#ifndef LIST_H

#define LIST_H

#define T      list_t
#define item_t int

typedef struct node_t *link_t;
typedef struct _T *T;

link_t newlink(item_t item, link_t next);
void dellink(link_t *l);
T list_init();
void list_finalize(T *t);
void list_show(T t);
void list_sort(T t);
void list_append(T t, item_t item);

#undef T
#undef item_t

#endif /* end of include guard: LIST_H */
