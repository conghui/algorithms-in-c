#ifndef DECK_H

#define DECK_H

#define T deck_t
typedef struct T *T;

T deck_init();
void deck_finalize(T t);
void deck_print(T t);
#undef T

#endif /* end of include guard: DECK_H */
