#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define T list_t
T list_new();
T list_newnode(int n);
void list_insert(T dest, T src);
void list_free(T head);
int is_even(const T node);
T list_cp_if(const T head, int (*fnc)(T node));
void list_for(T head, void (*fnc)(const T node));
void print(const T node);


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

T list_cp_if(const T head, int (*fnc)(T node))
{
    assert(head);
    T tmp;
    T newhead = list_new();
    T newtmp = newhead;

    for (tmp = head->next; tmp != NULL; tmp = tmp->next) {
        if (fnc(tmp)) {
            T nn = list_newnode(tmp->entry);
            list_insert(newtmp, nn);
            newtmp = newtmp->next;
        }
    }

    return newhead;
}

void list_for(const T head, void (*fnc)(const T node))
{
    assert(head);
    T tmp;

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
