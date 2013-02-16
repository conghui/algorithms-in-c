#ifndef CARD_H

#define CARD_H

#define T card_t
typedef struct T *T;

T card_init(int n, int s);
void card_finalize(T t);
void card_print(T t);

#undef T

#endif /* end of include guard: CARD_H */
