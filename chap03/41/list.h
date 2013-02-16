#ifndef LIST_H

#define LIST_H

#define T list_t

typedef struct T *T;
typedef const struct T *CT;
typedef const struct T *const CTC;

struct T {
    int entry;
    T next;
};

T list_new();
T list_newnode(int n);
void list_insert(T dest, const T src);
void list_free(T head);
void node_print(CTC node);
void list_for(T head, void (*fnc)(CTC));
void list_reverse(T head);
void list_sort(T head);
#endif /* end of include guard: LIST_H */
