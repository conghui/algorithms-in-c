#ifndef LIST_H

#define LIST_H

#define T list_t

typedef struct T *T;
typedef struct node *link;

typedef int Item;

struct node {
    Item entry;
    link next;
};

struct T {
    link head;
    link tail;
};

T list_init();
void list_finalize(T *l);
int list_empty(T t);
void list_push_back(T t, Item n);
void list_print(T t);
void dellink(link *l);

#undef T
#endif /* end of include guard: LIST_H */
