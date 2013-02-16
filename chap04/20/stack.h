#ifndef STACK_H

#define STACK_H

#define T Item
typedef double T;

void STACK_push(T entry);
T STACK_pop();
void error(const char *fmt, ...);
#undef T

#endif /* end of include guard: STACK_H */
