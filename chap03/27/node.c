#include <assert.h>
#include "node.h"

void moveone(node_t *x, node_t *t)
{
    assert(x && t);
    assert(t->next);
    /* isolate the next node of t */
    node_t *tmp = t->next;
    t->next = tmp->next;
    /* add tmp to x */
    tmp->next = x->next;
    x->next = tmp;
}
