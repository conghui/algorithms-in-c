#ifndef BTREE_H

#define BTREE_H

typedef struct node_t *link_t;
typedef const struct node_t *const_link_t;
typedef int item_t;

struct node_t {
    item_t item;   /* value of the node */
    link_t l;      /* left child        */
    link_t r;      /* right child       */
};

link_t newlink(item_t item, link_t l, link_t r);
void dellink(link_t *l);
link_t mytree();
void preorder_traverse(link_t root, void (*visit)(link_t));
void inorder_traverse(link_t root, void (*visit)(link_t));
void postorder_traverse(link_t root, void (*visit)(link_t));
#endif /* end of include guard: BTREE_H */
