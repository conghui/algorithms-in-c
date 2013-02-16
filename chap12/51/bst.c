#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "bst.h"
#include "alloc.h"

#define T bst_t

typedef struct node_t *link_t;
typedef void (*UnaryFunction)(link_t *);
typedef struct dnode_t *dlink_t;

struct dnode_t {
    item_t item;
    dlink_t next;
};

struct node_t {
    dlink_t data;
    link_t left;
    link_t right;
    size_t count;
};

struct _T {
    link_t root;
};

static link_t z;
static link_t zcnt;
static link_t newlink(item_t item, link_t left, link_t right, size_t count);
static void dellink(link_t *t);
static void postorder_traverse(link_t root, UnaryFunction f);
static link_t insert(link_t root, item_t item);
static item_t search(link_t root, item_t item);
static int lt(item_t a, item_t b);
static int eq(item_t a, item_t b);
static void inorder_traverseR(link_t root, UnaryFunction2 f);
static size_t count(link_t root, item_t item);

static dlink_t newdlink(item_t item, dlink_t next)
{
    dlink_t t = alloc(sizeof *t);
    t->item   = item;
    t->next   = next;
    return t;
}

static void deldlink(dlink_t *t)
{
    if (*t == NULL) {
        return;
    }

    free(*t);
    *t = NULL;
}

static link_t newlink(
    item_t item,
    link_t left,
    link_t right,
    size_t count)
{
    link_t t = alloc(sizeof *t);
    t->data  = newdlink(item, NULL);
    t->left  = left;
    t->right = right;
    t->count = count;
    return t;
}

static void dellink(link_t *t)
{
    if (t == NULL || *t == NULL) {
        return;
    }

    dlink_t tmp;

    while ((tmp = (*t)->data)) {
        (*t)->data = tmp->next;
        deldlink(&tmp);
    }

    free(*t);
    *t = NULL;
}

T bst_init()
{
    T t = alloc(sizeof *t);

    if (z == NULL) {
        z = newlink(0, NULL, NULL, 0);
    }

    zcnt++;
    t->root = z;
    return t;
}

void bst_finalize(T *t)
{
    if (*t == NULL) {
        return ;
    }

    postorder_traverse((*t)->root, dellink);
    free(*t);
    *t = NULL;

    if (--zcnt == 0) {
        dellink(&z);
    }
}

static void postorder_traverse(link_t root, UnaryFunction f)
{
    if (root == z) {
        return;
    }

    postorder_traverse(root->left, f);
    postorder_traverse(root->right, f);
    f(&root);
}

size_t bst_size(T t)
{
    return t->root->count;
}

void bst_insert(T t, item_t item)
{
    t->root = insert(t->root, item);
}

static link_t insert(link_t root, item_t item)
{
    if (root == z) { /* the tree is empty */
        return newlink(item, z, z, 1);
    }

    /* the tree is not empty */
    if (eq(item, root->data->item)) {
        root->data = newdlink(item, root->data);
    } else if (lt(item, root->data->item)) {
        root->left = insert(root->left, item);
    } else {
        root->right = insert(root->right, item);
    }

    /* after the insertion, the node has one more child */
    root->count++;
    return root;
}

item_t bst_search(T t, item_t item)
{
    return search(t->root, item);
}

static item_t search(link_t root, item_t item)
{
    if (root == z) {
        return null_item;
    }

    /* the root is not empty */
    if (eq(root->data->item, item)) {
        return item;
    } else if (lt(item, root->data->item)) {
        return search(root->left, item);
    } else {
        return search(root->right, item);
    }
}

static int lt(item_t a, item_t b)
{
    return a < b;
}
static int eq(item_t a, item_t b)
{
    return !lt(a, b) && !lt(b, a);
}

void bst_sort(T t, UnaryFunction2 f)
{
    inorder_traverseR(t->root, f);
}

static void inorder_traverseR(link_t root, UnaryFunction2 f)
{
    if (root == z) {
        return ;
    }

    inorder_traverseR(root->left, f);
    dlink_t cur;

    for (cur = root->data; cur != NULL; cur = cur->next) {
        f(cur->item);
    }

    inorder_traverseR(root->right, f);
}


size_t bst_count(T t, item_t item)
{
    return count(t->root, item);
}

static size_t count(link_t root, item_t item)
{
    if (root == z) {
        return 0;
    }

    if (eq(item, root->data->item)) {
        size_t cnt = 0;
        dlink_t cur;

        for (cur = root->data; cur != NULL; cur = cur->next) {
            cnt++;
        }

        return cnt;
    }

    if (lt(item, root->data->item)) {
        return count(root->left, item);
    } else {
        return count(root->right, item);
    }
}
