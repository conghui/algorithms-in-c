#ifndef STACK_H

#define STACK_H

typedef int Item;

int stack_full();
int stack_empty();
void stack_push(Item n);
Item stack_pop();

#endif /* end of include guard: STACK_H */
