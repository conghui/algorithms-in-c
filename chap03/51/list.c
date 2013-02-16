#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

#define T list_t


static T freelist;
static int has_init = 0;

T list_init(int n)
{
#ifdef MEMPOOL
    list_init_pool(n);
#else
    (void)n;
#endif
    T head = malloc(sizeof *head);
    assert(head);
    head->next  = NULL;
    head->entry = -1;
    return head;
}

void list_init_pool(int n)
{
    if (has_init) { /* the pool has been inited */
        return;
    }

    int i;
    freelist = calloc(n+1, sizeof *freelist);
    assert(freelist);

    for (i = 0; i < n+1; i++) {
        freelist[i].next = &freelist[i+1];
    }

    freelist[n].next = NULL;
    has_init = 1;
}

T list_newnode(int n)
{
#ifdef MEMPOOL
    T x      = list_delete_next(freelist);
    x->entry = n;
    x->next  = x;
#else
    T x = malloc(sizeof *x);
    assert(x);
    x->entry = n;
    x->next  = x; /* identify the last element */
#endif
    return x;
}


T list_delete_next(T node)
{
    assert(node && node->next);
    T tmp      = node->next;
    node->next = tmp->next;
    return tmp;
}

void list_insert_next(T dest, T src)
{
    assert(src && dest);

    if (dest->next == NULL) {
        src->next = src;
        dest->next = src;
    } else {
        src->next  = dest->next;
        dest->next = src;
    }
}

void list_free_node(T node)
{
    assert(node);
#ifdef MEMPOOL
    list_insert_next(freelist, node);
#else
    free(node);
#endif
}

void list_print(T head)
{
    assert(head);
    T cur = head->next;

    if (cur == NULL) {
        return ;
    }

    do {
        printf("%d ", cur->entry);
        cur = cur->next;
    } while (cur != head->next);

    putchar('\n');
}

void list_delete(T head)
{
    T cur = head->next;

    while (cur != cur->next) {
        T tmp = list_delete_next(cur);
        /*printf("%d  ", tmp->entry);*/
        list_free_node(tmp);
    }

    list_free_node(cur);
    free(head);
#ifdef MEMPOOL
    free(freelist);
    has_init = 0;
#endif
}
