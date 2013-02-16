#ifndef LIST_H

#define LIST_H

#define T list_t
typedef struct T *T;

struct T {
    int entry;
    T   next;
};

T list_new();
void list_insert(T dest, T src);
void list_free(T head);
T list_newnode(int n);
void list_print(T head);
#undef T

#endif /* end of include guard: LIST_H */
