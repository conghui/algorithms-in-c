#ifndef DEQUE_H

#define DEQUE_H


typedef char      Item;

void deque_push_front(Item n);
void deque_push_back(Item n);
Item deque_pop_front();
Item deque_pop_back();
int deque_empty();

Item deque_back();
Item deque_front();

#endif /* end of include guard: DEQUE_H */
