#ifndef QUEUE_H

#define QUEUE_H

#define IGNORE_NEW 1

typedef int Item;

void queue_push(Item n);
void queue_init(void);
Item queue_pop();
int queue_empty();
void queue_finalize();
#endif /* end of include guard: QUEUE_H */
