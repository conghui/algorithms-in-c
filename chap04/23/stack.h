#ifndef STACK_H

#define STACK_H

#include <stddef.h>

#define T node_t

typedef struct T *T;
typedef int       Item;

struct T {
    Item entry;
    T    prev;
    T    next;
};

void *alloc(size_t size);
T newnode(Item n, T prev, T next);
void stack_push(Item n);
Item stack_pop();
int stack_empty();
void stack_print();
void stack_clear();

#undef T

#endif /* end of include guard: STACK_H */
