#ifndef STACK_H

#define STACK_H

#define T node_t

#include <stddef.h>
typedef struct T *T;
typedef int       Item;

struct T {
    Item entry;
    T    next;
};

void *alloc(size_t size);
T newnode(Item n, T next);
void stack_push(Item n);
Item stack_pop();
int stack_empty();
void stack_clear();
void stack_print();

#undef T

#endif /* end of include guard: STACK_H */
