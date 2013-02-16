#ifndef ST_H

#define ST_H

#define T st_t

#include <stddef.h>
#define true 1
#define false 0
typedef int key_t;
typedef int bool;
typedef struct item_t *item_t;
typedef struct T *T;

typedef item_t *InputIterator;
typedef void (*UnaryFunction)(item_t);

item_t newitem(key_t key, const char *str);
void delitem(item_t *t);
T st_init(size_t capacity);
void st_finalize(T *t);
void st_insert(T t, item_t item);
item_t st_search(T t, key_t k);
item_t st_select(T t, size_t k);
void st_sort(T t, UnaryFunction f);
UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f);
bool st_full(T t);
bool st_empty(T t);
const char *getstr(item_t x);
key_t getkey(item_t v);
size_t st_size(T t);
void st_delete(T t, item_t x);
void st_searchinsert(T t, item_t item);

#undef T

#endif /* end of include guard: ST_H */
