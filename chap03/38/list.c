#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

link new_list()
{
    link head  = malloc(sizeof *head);
    assert(head);
    head->next = NULL;
    return head;
}
link new_node(int n)
{
    link nn = malloc(sizeof *nn);
    assert(nn);
    nn->entry = n;
    nn->next  = NULL;
    return nn;
}

void list_free(link head)
{
    link tmp;

    while ((tmp = head->next) != NULL) {
        head->next = tmp->next;
        free(tmp);
    }

    free(head);
}

void list_insert(link dest, link src)
{
    src->next  = dest->next;
    dest->next = src;
}

link list_copy(link dest, link src)
{
    link psrc;  /* points to src link list */
    link pdest; /* points the dest link list */

    for (psrc = src->next, pdest = dest; psrc != NULL;
         psrc = psrc->next, pdest = pdest->next) {
        link nn = new_node(psrc->entry);
        list_insert(pdest, nn);
    }

    return dest;
}

void list_print(link head)
{
    for (head = head->next; head != NULL; head = head->next) {
        printf("%3d", head->entry);
    }

    putchar('\n');
}
