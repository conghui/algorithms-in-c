#ifndef STACKARRAY_H

#define STACKARRAY_H


#define T Item
typedef int Item;

int stackArray_isfull();
int stackArray_isempty();
void stackArray_push(T n);
T stackArray_pop();
int stackArray_count();

#undef T

#endif /* end of include guard: STACKARRAY_H */
