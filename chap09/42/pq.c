#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "pq.h"

#define T pq_t
#define item_t int

typedef struct node_t *link_t;
typedef void (*Function)(link_t *);

struct node_t {
    item_t item;
    link_t parent;
    link_t left;
    link_t right;
};

struct _T {
    link_t root;
    link_t last;
};

static void *alloc(size_t size);
static link_t newlink(item_t item, link_t parent, link_t left, link_t right);
static void dellink(link_t *t);
static void postorder_delete(link_t *t, Function f);
T pq_init();
void pq_finalize(T *t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(
    item_t item,
    link_t parent,
    link_t left,
    link_t right)
{
    link_t t  = alloc(sizeof *t);
    t->item   = item;
    t->parent = parent;
    t->left   = left;
    t->right  = right;
    return t;
}

static void dellink(link_t *t)
{
    free(*t);
    *t = NULL;
}

T pq_init()
{
    T t     = alloc(sizeof *t);
    t->root = NULL;
    t->last = NULL;
    return t;
}

/* this function should impletement carefully */
void pq_finalize(T *t)
{
    postorder_delete(&(*t)->root, dellink);
}

static void postorder_delete(link_t *t, Function f)
{
    if (*t == NULL) {
        return ;
    }

    postorder_delete(&(*t)->left, f);
    postorder_delete(&(*t)->right, f);
    f(t);
}

void pq_insert(T t, item_t item)
{
    if (t->root == NULL) { /* the tree is empty */
        t->root = newlink(item, NULL, NULL, NULL);
        t->last = t->root;
    } else { /* the tree is not empty */
    }
}


