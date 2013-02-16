#include "node.h"

int distance(const node_t *s, const node_t *t)
{
    int cnt;

    for (cnt = 0; s->next != t; s = s->next, cnt++) ;

    return cnt;
}
