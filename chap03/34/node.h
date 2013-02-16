#ifndef NODE_H

#define NODE_H

typedef struct _node_t {
    int             entry;
    struct _node_t *next;
} node_t;

node_t *newNode(int entry);
void listInsert(node_t *curnode, node_t *newnode);
void mvB2last(node_t *head);
void printNode(const node_t *head);
void freeList(node_t *head);

#endif /* end of include guard: NODE_H */
