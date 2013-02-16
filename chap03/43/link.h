#ifndef LINK_H

#define LINK_H

#define T list_t

typedef struct T *T;

typedef const struct T *CT;

struct T {
    int entry;
    T next;
};

T list_new();
T list_new_node(int n);
void list_insert_next(T dest, T src);
void list_delete(T head);
void list_print(CT head);

#undef T

#endif /* end of include guard: LINK_H */
