#ifndef LIST_H

#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _node_t {
    int entry;
    struct _node_t *next;
} node_t;

typedef node_t *link;

link listNew(int n);
void listInsert(link dest, link src);
void listFree(link head);
void listResort(link head);

void listPrint(link head);
#endif /* end of include guard: LIST_H */
