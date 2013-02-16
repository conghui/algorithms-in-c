#ifndef LIST_H

#define LIST_H

#define T list_t
typedef struct T *T;
typedef const struct T *CT;

struct T {
    int entry;
    T next;
};

T list_new();
T list_newnode(int n);
void list_insert_next(T dest, T src);
void list_delete(T head);
void node_print(T node);
void list_for(T head, void (*fnc)(T));
#undef T

#endif /* end of include guard: LIST_H */
