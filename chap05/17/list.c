#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "list.h"

#define T list_t
static void *alloc(size_t size);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

link newlink(int entry, link next)
{
    link l   = alloc(sizeof * l);
    l->next  = next;
    l->entry = entry;
    return l;
}

void dellink(link *l)
{
    free(*l);
    *l = NULL;
}

T list_init()
{
    T t     = alloc(sizeof * t);
    t->head = NULL;
}

void list_finalize(T *t)
{
    link tmp;

    if ((*t)->head == NULL) {
        free(*t);
        *t = NULL;
        return ;
    }

    tmp = (*t)->head;
    (*t)->head = tmp->next;
    free(tmp);
    list_finalize(t);
}

void list_insert_front(T t, int entry)
{
    t->head = newlink(entry, t->head);
}

void list_print(T t)
{
    link tmp;

    for (tmp = t->head; tmp != NULL; tmp = tmp->next) {
        printf("%d ", tmp->entry);
    }

    putchar('\n');
}
