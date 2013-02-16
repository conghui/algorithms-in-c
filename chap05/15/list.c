#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

#define T list_t
static void *alloc(size_t size);
static link newlink(Item n, link next);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link newlink(Item n, link next)
{
    link l   = alloc(sizeof * l);
    l->entry = n;
    l->next  = next;
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
    t->tail = NULL;
    return t;
}

void list_finalize(T *l)
{
    link tmp;

    while ((tmp = (*l)->head) != NULL) {
        (*l)->head = tmp->next;
        dellink(&tmp);
    }

    dellink(&tmp);
    free(*l);
    *l = NULL;
}

int list_empty(T t)
{
    return t->head == NULL;
}

void list_push_back(T t, Item n)
{
    link l;

    if (list_empty(t)) {
        l       = newlink(n, NULL);
        t->head = l;
        t->tail = l;
        return ;
    }

    /* the list is not empty */
    l = newlink(n, NULL);
    t->tail->next = l;
    t->tail       = l;
}

void list_print(T t)
{
    link tmp;

    for (tmp = t->head; tmp != NULL; tmp = tmp->next) {
        printf("%d ", tmp->entry);
    }

    putchar('\n');
}
