#ifndef QUEUE_H

#define QUEUE_H

typedef int Item;

void queue_init();
void queue_push(Item n);
Item queue_pop();
int queue_empty();
int queue_full();

#endif /* end of include guard: QUEUE_H */
