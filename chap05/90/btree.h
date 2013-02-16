#ifndef BTREE_H

#define BTREE_H

#define T btree_t
#define item_t int

typedef struct T *T;
typedef struct node_t *link_t;
typedef const struct node_t *const_link_t;

struct node_t {
    item_t item;
    link_t left;
    link_t right;
};

struct T {
    link_t root;
};

extern int count;
T btree_init(char *str);
void btree_preorder_traverse(T t, void (*visit)(link_t));
int btree_special_node_cnt(T t);
void btree_finalize(T *t);
int btree_internal_length(T t);
#undef T
#undef item_t
#endif /* end of include guard: BTREE_H */
