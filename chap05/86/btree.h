#ifndef BTREE_H

#define BTREE_H

#define T      btree_t
#define item_t int

typedef struct node_t       *link_t;
typedef const struct node_t *const_link_t;
typedef struct T            *T;

struct T {
    link_t root;
};

struct node_t {
    item_t item;
    link_t left;
    link_t right;
};

link_t newlink(item_t item, link_t left, link_t right);
void dellink(link_t *l);
T btree_init();
size_t btree_leaf_count(T t);
void btree_finalize(T *t);

#undef T
#undef item_t

#endif /* end of include guard: BTREE_H */
