#ifndef STACK_H

#define STACK_H

#define T Item
typedef int T;

void stack_init(size_t size);
void stack_free();
void stack_push(Item n);
int stack_full();
int stack_empty();
Item stack_pop();
size_t stack_count();

#undef T

#endif /* end of include guard: STACK_H */
