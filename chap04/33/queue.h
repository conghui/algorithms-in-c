#ifndef QUEUE_H

#define QUEUE_H

#define T node_t
typedef struct T *T;
typedef int       Item;

struct T {
    Item entry;
    T    next;
};

T newnode(Item n, T next);
void queue_push(Item n);
Item queue_pop();
int queue_empty();

#undef T
#endif /* end of include guard: QUEUE_H */
