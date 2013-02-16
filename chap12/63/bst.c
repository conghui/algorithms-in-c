#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>
#include <ctype.h>

#include "bst.h"
#include "alloc.h"

#define T bst_t

typedef struct {
    item_t item;
} node_t;

struct _T {
    node_t *data;
    int    *left;
    int    *right;
    size_t  capacity;
    size_t  size;
};

static node_t z = {INT_MIN};
static int null_index = INT_MIN;

static int insert(T t, int index, item_t item);
T bst_init(size_t capacity);
void bst_finalize(T *t);
void bst_insert(T t, item_t item);
int bst_empty(T t);

T bst_init(size_t capacity)
{
    T t         = alloc(sizeof *t);
    t->data     = alloc(capacity * sizeof *t->data);
    t->left     = alloc(capacity * sizeof *t->left);
    t->right    = alloc(capacity * sizeof *t->right);
    t->capacity = capacity;
    t->size     = 0;
    size_t i;

    for (i = 0; i < capacity; i++) {
        t->data[i] = z;
        t->left[i]  = null_index;
        t->right[i] = null_index;
    }

    return t;
}

void bst_finalize(T *t)
{
    if (*t == NULL) {
        return;
    }

    free((*t)->left);
    free((*t)->right);
    free((*t)->data);
    free(*t);
    *t = NULL;
}

void bst_insert(T t, item_t item)
{
    insert(t, 0, item);
}

static int eqnode(node_t a, node_t b)
{
    return a.item == b.item;
}

static int lt(item_t a, item_t b)
{
    return a < b;
}
static int insert(T t, int index, item_t item)
{
    if (index == null_index || eqnode(t->data[index], z)) {
        t->data[t->size++] = (node_t) {
            item
        };
        return t->size - 1;
    } else if (lt(item, t->data[index].item)) {
        int newindex = insert(t, t->left[index], item);

        if (t->left[index] == null_index) {
            t->left[index] = newindex;
        }
    } else {
        int newindex = insert(t, t->right[index], item);

        if (t->right[index] == null_index) {
            t->right[index] = newindex;
        }
    }

    return t->size - 1;
}

static void inorder_traverse(T t, int index, UnaryFunction2 f)
{
    if (index == null_index || eqnode(t->data[index], z)) {
        return ;
    }

    inorder_traverse(t, t->left[index], f);
    f(t->data[index].item);
    inorder_traverse(t, t->right[index], f);
}

void bst_sort(T t, UnaryFunction2 f)
{
    inorder_traverse(t, 0, f);
}

int bst_empty(T t)
{
    return t->size == 0;
}
