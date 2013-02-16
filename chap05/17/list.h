#ifndef LIST_H

#define LIST_H

#define T list_t

typedef struct T *T;
typedef struct node_t *link;

struct node_t {
    int entry;
    link next;
};

struct T {
    link head;
};

link newlink(int entry, link next);
void dellink(link *l);
T list_init();
void list_finalize(T *t);
void list_insert_front(T t, int entry);
void list_print(T t);

#undef T
#endif /* end of include guard: LIST_H */
