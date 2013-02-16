#include "node.h"

link list_new_node(int entry)
{
    link newnode;
    newnode = malloc(sizeof *newnode);
    assert(newnode);
    newnode->entry = entry;
    newnode->next = NULL;
    return newnode;
}

void list_insert(link dest, link src)
{
    src->next = dest->next;
    dest->next = src;
}

void list_free(link head)
{
    link curnode;

    while ((curnode = head->next) != NULL) {
        head->next = curnode->next;
        free(curnode);
    }
}

void list_mv1st(link head)
{
    link small;
    link prev_small;
    link cur;
    link prev;
    prev_small = head;
    small = head->next;

    if (small == NULL) {
        fprintf(stderr, "the list is empty\n");
        return;
    }

    for (prev = small, cur = small->next; cur != NULL;
         prev = cur, cur = cur->next) {
        if (cur->entry < small->entry) {
            prev_small = prev;
            small = cur;
        }
    }

    /* isolate the smallest node */
    prev_small->next = small->next;
    /* put the smallest node to the first */
    small->next = head->next;
    head->next = small;
}

void list_print(link head)
{
    for (head = head->next; head != NULL; head = head->next) {
        printf("%d ", head->entry);
    }
}
