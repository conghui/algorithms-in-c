#ifndef LIST_H

#define LIST_H

#define T list_t
typedef struct T *T;

struct T {
    int entry;
    T   next;
};

T list_init(int n);
void list_init_pool(int n);
T list_newnode(int n);
T list_delete_next(T node);
void list_insert_next(T dest, T src);
void list_free_node(T node);
void list_print(T head);
void list_delete(T head);
#undef T

#endif /* end of include guard: LIST_H */
