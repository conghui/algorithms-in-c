#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "list.h"

#define T list_t

T list_new()
{
    T  head = malloc(sizeof *head);
    assert(head);
    head->next = NULL;
    return head;
}

T list_newnode(int n)
{
    T nn = malloc(sizeof *nn);
    assert(nn);
    nn->next  = NULL;
    nn->entry = n;
    return nn;
}

void list_insert(T dest, T src)
{
    assert(dest && src);
    src->next  = dest->next;
    dest->next = src;
}

void list_free(T head)
{
    T tmp;

    if (head == NULL) {
        return ;
    }

    while ((tmp = head->next) != NULL) {
        head->next = tmp->next;
        free(tmp);
    }

    free(head);
}

void list_print(T head)
{
    T cur;

    for (cur = head->next; cur->next != NULL; cur = cur->next) {
        printf("%d -> ", cur->entry);
    }

    printf("%d\n", cur->entry);
}
