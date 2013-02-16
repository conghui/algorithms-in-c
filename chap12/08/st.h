#ifndef ST_H

#define ST_H

#include <stddef.h>
#define T st_t

typedef int key_t;
typedef struct _item *item_t;
typedef struct _T *T;

typedef int bool;
typedef bool (*Predicate)(item_t);
typedef item_t *InputIterator;
typedef void (*UnaryFunction)(item_t);

T st_init(key_t maxkey);
void st_finalize(T *_t);
int st_count(T t);
void st_insert(T t, item_t x);
item_t st_search(T t, key_t key);
void st_delete(T t, item_t item);
item_t st_select(T t, int k);
void st_sort(T t, UnaryFunction f);
#undef T

#endif /* end of include guard: ST_H */
