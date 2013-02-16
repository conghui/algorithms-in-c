#ifndef LIST_H

#define LIST_H

typedef struct _node_t {
    int entry;
    struct _node_t *next;
} node_t;

typedef node_t *link;

link new_node(int n);
link new_list();
void list_free(link head);
void list_insert(link dest, link src);
link list_copy(link dest, link src);
void list_print(link head);
#endif /* end of include guard: LIST_H */
