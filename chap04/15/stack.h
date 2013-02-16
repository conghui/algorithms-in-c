#ifndef STACK_H

#define STACK_H

void stack_push(const char *item);
int stack_full();
void error(const char *fmt, ...);
int stack_empty();
void stack_pop(char *store);
#endif /* end of include guard: STACK_H */
