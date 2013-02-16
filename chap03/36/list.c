#include "list.h"

link listNew(int n)
{
    link newnode;
    newnode        = malloc(sizeof *newnode);
    newnode->entry = n;
    newnode->next  = NULL;
    return newnode;
}

void listInsert(link dest, link src)
{
    src->next  = dest->next;
    dest->next = src;
}

void listFree(link head)
{
    link curnode;

    while ((curnode = head->next) != NULL) {
        head->next = curnode->next;
        free(curnode);
    }
}

void listResort(link head)
{
    int  cnt;         /* # of nodes past                                   */
    link evenBegin;   /* points to the first even element, such as 2nd one */
    link even;        /* points to the last even element                   */
    link odd;         /* points to the last odd element                    */
    link cur;
    odd = head->next;

    if (odd == NULL) {
        return ;
    }

    evenBegin = even = odd->next;

    if (even == NULL) {
        return ;
    }

    for (cnt = 3, cur = even->next; cur != NULL; cnt++, cur = cur->next) {
        if (cnt % 2) {
            odd->next = cur;
            odd       = cur;
        } else {
            even->next = cur;
            even       = cur;
        }
    }

    odd->next  = evenBegin;
    even->next = NULL;
}

void listPrint(link head)
{
    for (head = head->next; head != NULL; head = head->next) {
        printf("%d ", head->entry);
    }

    putchar('\n');
}
