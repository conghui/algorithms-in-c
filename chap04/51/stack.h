#ifndef STACK_H

#define STACK_H

typedef int Item;

void stack_init(size_t size);
void stack_push(Item n);
Item stack_pop();
int stack_empty();

void stack_final();
#endif /* end of include guard: STACK_H */
