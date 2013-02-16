#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

T list_new()
{
    T head = malloc(sizeof *head);
    assert(head);
    head->next = NULL;
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

void list_insert(T dest, const T src)
{
    assert(dest && src);
    src->next   = dest->next;
    dest->next = src;
}

void list_free(T head)
{
    T tmp;
    assert(head);

    while ((tmp = head->next) != NULL) {
        head->next = tmp->next;
        free(tmp);
    }

    free(head);
}

void node_print(CTC node)
{
    assert(node);
    printf("%3d", node->entry);

    if (node->next == NULL) {
        putchar('\n');
    }
}

void list_for(T head, void (*fnc)(CTC))
{
    assert(head);
    CT tmp;

    for (tmp = head->next; tmp != NULL; tmp = tmp->next) {
        fnc(tmp);
    }
}

void list_reverse(T head)
{
    assert(head);
    T prev;
    T cur;
    T next;
    prev = NULL;
    cur  = head->next;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev      = cur;
        cur       = next;
    }

    head->next = prev;
}

void list_sort(T head)
{
    assert(head);
    T cur;
    T next;
    T sortlist;
    cur = head->next;
    sortlist = list_new();

    while (cur != NULL) {
        next = cur->next;   /* save next unsorted element */
        T sortcur;

        /* find  the location to insert it */
        for (sortcur = sortlist; sortcur->next != NULL;
             sortcur = sortcur->next) {
            if (sortcur->next->entry > cur->entry) {
                break;
            }
        }

        /* find out the location, and insert it */
        cur->next     = sortcur->next;
        sortcur->next = cur;
        cur  = next;
    }

    head->next = sortlist->next;
    sortlist->next = NULL;
    free(sortlist);
}
