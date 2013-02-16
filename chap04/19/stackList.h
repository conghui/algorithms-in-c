#ifndef STACKLIST_H

#define STACKLIST_H

#define T stack_t
typedef struct T *T;

struct T {
    int entry;
    T   next;
};


T stackList_newnode(int n);
void stackList_push(int n);
int stackList_pop();
int stackList_count();
int stackList_empty();

#undef T

#endif /* end of include guard: STACKLIST_H */
