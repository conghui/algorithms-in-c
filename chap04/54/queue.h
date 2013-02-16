#ifndef QUEUE_H

#define QUEUE_H

typedef int Item;

void queue_init(size_t n);
int queue_full();
int queue_empty();
void queue_push(Item n);
Item queue_pop();
void queue_finalize();

#endif /* end of include guard: QUEUE_H */
