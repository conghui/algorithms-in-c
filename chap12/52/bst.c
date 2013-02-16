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

struct node_t {
    item_t item;
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
static link_t search_insert(link_t root, item_t item);
static size_t count(link_t root, item_t item);
static int le(item_t a, item_t b);

static link_t newlink(
    item_t item,
    link_t left,
    link_t right,
    size_t count)
{
    link_t t = alloc(sizeof *t);
    t->item  = item;
    t->left  = left;
    t->right = right;
    t->count = count;
    return t;
}

static void dellink(link_t *t)
{
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
    if (t->root == z) { /* the tree is empty */
        t->root = newlink(item, z, z, 1);
        return ;
    }

    /* the tree is not empty */
    link_t root = t->root;
    link_t parent;
    int left = 0;

    while (root != z) {
        parent = root;
        root   = (left = lt(item, root->item)) == 1 ?
                 root->left : root->right;
    }

    root = newlink(item, z, z, 1);

    if (left) {
        parent->left = root;
    } else {
        parent->right = root;
    }
}

static link_t insert(link_t root, item_t item)
{
    if (root == z) { /* the tree is empty */
        return newlink(item, z, z, 1);
    }

    /* the tree is not empty */
    if (lt(item, root->item)) {
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
    if (eq(root->item, item)) {
        return item;
    } else if (lt(item, root->item)) {
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
    f(root->item);
    inorder_traverseR(root->right, f);
}

static link_t search_insert(link_t root, item_t item)
{
    if (root == z) {
        return newlink(item, z, z, 1);
    }

    /* the same item exist */
    if (eq(item, root->item)) {
        return root;
    }

    /* we need to insert the item */
    if (lt(item, root->item)) {
        root->left = search_insert(root->left, item);
    } else {
        root->right = search_insert(root->right, item);
    }

    root->count++;
    return root;
}

void bst_search_insert(T t, item_t item)
{
    t->root = search_insert(t->root, item);
}

size_t bst_count(T t, item_t item)
{
    return count(t->root, item);
}

static size_t count(link_t root, item_t item)
{
    compare_cnt++;

    if (root == z) {
        return 0;
    }

    int lcount = 0;
    int rcount = 0;

    if (lt(item, root->item)) {
        lcount = count(root->left, item);
    } else if (le(root->item, item)) {
        rcount = count(root->right, item);
    }

    return root->item == item ? 1 + lcount + rcount : lcount + rcount;
}

static int le(item_t a, item_t b)
{
    return lt(a, b) || eq(a, b);
}
