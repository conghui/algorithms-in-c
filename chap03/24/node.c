#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "node.h"

static node_t *cirlist = NULL;

node_t *get_cir_list()
{
    if (cirlist != NULL) {
        return cirlist;
    }

    node_t *n = malloc(sizeof *n);

    if (n == NULL) {
        fprintf(stderr, "memory is not enough\n");
        exit(EXIT_FAILURE);
    }

    n->entry = 0;
    n->next = n;
    cirlist = n;
    return cirlist;
}

int list_size()
{
    int cnt;
    node_t *tail = cirlist;

    if (cirlist == NULL) {
        return 0;
    }

    for (cnt = 1; tail != cirlist->next; cnt++) {
        cirlist = cirlist->next;
    }

    return cnt;
}

void list_add(int x)
{
    node_t *n = malloc(sizeof *n);
    assert(n);
    n->entry = x;

    if (cirlist == NULL) {
        n->next = n;
    } else {
        n->next = cirlist->next;
        cirlist->next = n;
    }

    cirlist = n;
}

void list_free()
{
    node_t *tail = cirlist;
    node_t *tmp;

    if (cirlist == NULL) {
        return;
    }

    while (cirlist->next != tail) {
        tmp = cirlist->next;
        cirlist->next = tmp->next;
        free(tmp);
    }

    free(cirlist);
    cirlist = NULL;
}
