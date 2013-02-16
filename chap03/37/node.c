#include "node.h"

/* swap the value instead of the pointer may be easier */
void list_swap(node_t *first, node_t *second)
{
    int tmp       = first->entry;
    first->entry  = second->entry;
    second->entry = tmp;
}
