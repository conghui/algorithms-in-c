#ifndef QUEUE_H

#define QUEUE_H

/*#define DEL_OLD 1*/
#define IGNORE_NEW 1


typedef int Item;

void queue_init(size_t n);
int queue_empty();
void queue_push(Item n);
Item queue_pop();
void queue_finalize();

#endif /* end of include guard: QUEUE_H */
