#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "node.h"

node_t *newNode(int entry)
{
    node_t *newnode;
    newnode = malloc(sizeof *newnode);
    assert(newnode);
    newnode->entry = entry;
    newnode->next = NULL;
    return newnode;
}

void listInsert(node_t *curnode, node_t *newnode)
{
    newnode->next = curnode->next;
    curnode->next = newnode;
}

void mvB2last(node_t *head)
{
    node_t *prevbig;   /* bignode->next points to the biggest node */
    node_t *big;       /* points to the biggest node               */
    node_t *cur;       /* current node                             */
    node_t *prev;      /* previous node                            */

    if (head->next == NULL) { /* the list is empty */
        fprintf(stderr, "the link list is empty\n");
        return;
    }

    prevbig = head;
    big = head->next;

    /* search for the biggest node */
    for (prev = big, cur = big->next; cur != NULL;
         prev = cur, cur = cur->next) {
        if (cur->entry > big->entry) {
            prevbig = prev;
            big = cur;
        }
    }

    /* connect prevbig to the big->next */
    prevbig->next = big->next;
    /* now prev points to the last node, make it points to biggest node */
    prev->next = big;
    big->next = NULL;
}

void printNode(const node_t *head)
{
    node_t *cur;

    for (cur = head->next; cur != NULL; cur = cur->next) {
        printf("%d ", cur->entry);
    }

    putchar('\n');
}

void freeList(node_t *head)
{
    node_t *cur;

    for (cur = head->next; cur != NULL; cur = head->next) {
        head->next = cur->next;
        free(cur);
    }
}
