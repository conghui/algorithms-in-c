#ifndef NODE_H

#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct _node_t {
    int entry;
    struct _node_t *next;
} node_t;

typedef node_t *link;

link list_new_node(int entry);
void list_insert(link dest, link src);
void list_free(link head);
void list_mv1st(link head);
void list_print(link head);

#endif /* end of include guard: NODE_H */
