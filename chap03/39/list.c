#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define T list_t


T list_new()
{
    T head = malloc(sizeof *head);
    assert(head);
    head->next = NULL;
    return head;
}

T list_newnode(int n)
{
    T tmp = malloc(sizeof *tmp);
    assert(tmp);
    tmp->entry = n;
    tmp->next  = NULL;
    return tmp;
}

void list_insert(T dest, T src)
{
    assert(src != NULL);
    assert(dest != NULL);
    src->next  = dest->next;
    dest->next = src;
}

void list_free(T head)
{
    T tmp;
    assert(head != NULL);

    while ((tmp = head->next) != NULL) {
        head->next = tmp->next;
        free(tmp);
    }

    free(head);
}

int is_even(const T node)
{
    assert(node != NULL);
    return node->entry % 2  == 0 ? 1 : 0;
}

void list_rm_if(T head, int (*fnc)(T node))
{
    assert(head);
    T tmp;
    T prev;

    for (prev = head, tmp = head->next; tmp != NULL;
         prev = tmp, tmp = tmp->next) {
        if (fnc(tmp)) {
            prev->next = tmp->next;
            free(tmp);
        }
    }
}

void list_for(T head, void (*fnc)(const T node))
{
    T tmp;
    assert(head);

    for (tmp = head->next; tmp != NULL; tmp = tmp->next) {
        fnc(tmp);
    }
}

void print(const T node)
{
    assert(node);
    printf("%3d", node->entry);

    if (node->next == NULL) {
        putchar('\n');
    }
}
