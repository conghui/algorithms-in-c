#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "list.h"

#define T list_t

T list_new()
{
    T head = malloc(sizeof *head);
    assert(head);
    head->next  = NULL;
    head->entry = INT_MIN;
    return head;
}

T list_newnode(int n)
{
    T newnode = malloc(sizeof *newnode);
    assert(newnode);
    newnode->entry = n;
    newnode->next  = NULL;
    return newnode;
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
        return ;
    }

    T cur;

    while ((cur = head->next) != NULL) {
        head->next = cur->next;
        free(cur);
    }

    free(head);
}

void node_print(T node)
{
    assert(node);
    printf("%d ", node->entry);

    if (node->next == NULL) { /* the last entry */
        putchar('\n');
    }
}

void list_for(T head, void (*fnc)(T))
{
    assert(head);
    T cur = head->next;

    for (; cur != NULL; cur = cur->next) {
        fnc(cur);
    }
}
