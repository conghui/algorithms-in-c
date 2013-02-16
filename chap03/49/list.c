#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

#define T list_t

T list_init()
{
    T head = malloc(sizeof *head);
    assert(head);
    head->next  = NULL;
    head->entry = -1;
    return head;
}

T list_newnode(int n)
{
    T nn = malloc(sizeof *nn);
    assert(nn);
    nn->entry = n;
    nn->next  = NULL;
    return nn;
}

void list_insert_next(T dest, T src)
{
    assert(src && dest);
    src->next  = dest->next;
    dest->next = src;
}

void list_delete(T head)
{
    if (head == NULL) {
        return;
    }

    T cur;

    while ((cur = head->next) != NULL) {
        head->next = cur->next;
        free(cur);
    }

    free(head);
}

void list_print(T head)
{
    T cur;

    for (cur = head->next; cur != NULL; cur = cur->next) {
        printf("%d ", cur->entry);
    }

    putchar('\n');
}
