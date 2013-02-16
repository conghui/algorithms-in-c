#ifndef DEQUE_H

#define DEQUE_H

#define T link

typedef struct T *T;
typedef char      Item;

struct T {
    Item entry;
    T    next;
    T    prev;
};

void deque_push_front(Item n);
void deque_push_back(Item n);
Item deque_pop_front();
Item deque_pop_back();
int deque_empty();
void deque_dump();
Item deque_back();
Item deque_front();
#undef T

#endif /* end of include guard: DEQUE_H */
