#ifndef NODE_H

#define NODE_H

typedef struct _node_t {
    int entry;
    struct _node_t *next;
} node_t;

node_t *get_cir_list();
int list_size();
void list_add(int x);

void list_free();
#endif /* end of include guard: NODE_H */
