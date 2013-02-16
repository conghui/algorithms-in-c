#ifndef TYPE_H

#define TYPE_H


typedef int item_t;
typedef item_t *Iterator;
typedef item_t (*Generator)();
typedef void (*Function)(item_t *);
typedef int (*Compare)(item_t, item_t);

#endif /* end of include guard: TYPE_H */
