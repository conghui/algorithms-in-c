#ifndef STACK_H

#define STACK_H

#define IGNORE_OLD 1
/*#define IGNORE_NEW 1*/

typedef int Item;

void stack_push(Item n);
Item stack_pop();
int stack_empty();
#endif /* end of include guard: STACK_H */
