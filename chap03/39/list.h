#ifndef LIST_H

#define LIST_H

#define T list_t
typedef struct T *T;

struct T {
    int entry;
    T next;
};

T list_new();
T list_newnode(int n);
void list_insert(T dest, T src);
void list_free(T head);
int is_even(const T node);
void list_rm_if(T head, int (*fnc)(T node));
void list_for(T head, void (*fnc)(const T node));
void print(const T node);
#endif /* end of include guard: LIST_H */
