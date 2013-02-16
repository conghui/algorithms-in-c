#include <assert.h>
#include "node.h"

void merge(node_t *x, node_t *t)
{
    assert(x && t);
    node_t *tfront = t->next;
    t->next = x->next;
    x->next = tfront;
}
