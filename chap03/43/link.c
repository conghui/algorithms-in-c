#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "link.h"

#define T list_t
T list_new();
T list_new_node(int n);
void list_insert_next(T dest, T src);
void list_delete(T head);
void list_print(CT head);

T list_new()
{
    T head = malloc(sizeof *head);
    assert(head);
    head->next = NULL;
    return head;
}

T list_new_node(int n)
{
    T newnode = malloc(sizeof *newnode);
    assert(newnode);
    newnode->entry = n;
    newnode->next  = NULL;
    return newnode;
}

void list_insert_next(T dest, T src)
{
    if (dest->next == NULL) { /* empty list */
        src->next  = src;
        dest->next = src;
    } else {
        src->next  = dest->next;
        dest->next = src;
    }
}

void list_delete(T head)
{
    if (head == NULL) {
        return ;
    } else if (head->next == NULL) { /* only have a head */
        free(head);
        return ;
    }

    T cur = head->next;

    while (cur->next != cur) { /* at least one element */
        T tmp     = cur->next;
        cur->next = tmp->next;
        free(tmp);
    }

    free(cur);
    free(head);
}

void list_print(CT head)
{
    CT cur;

    if (head == NULL || head->next == NULL) {
        return ;
    }

    cur = head->next;

    do {
        printf("%d ", cur->entry);
        cur = cur->next;
    } while (cur != head->next);

    putchar('\n');
}
