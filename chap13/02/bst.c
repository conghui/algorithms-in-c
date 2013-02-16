#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "bst.h"

#define T bst_t

typedef struct node_t *link_t;

struct node_t
{
    int    item;
    size_t size;
    link_t left;
    link_t right;
};

struct T
{
    link_t root;
};

static struct node_t null_node = {
    0,
    0,
    NULL,
    NULL
};

static link_t null_link = &null_node;
static void *alloc(size_t size);
static link_t newlink(int item, size_t size, link_t left, link_t right);
static void dellink(link_t *t);
static void postorder_visit(link_t root, void (*f)(link_t *));
static link_t insert_bottom(link_t root, int item);
static int powerof2(size_t n);
static link_t balance_recursive(link_t root);
static link_t partition_recursive(link_t root, size_t k);
static size_t count_size(link_t root);
static link_t rotate_right(link_t root);
static link_t rotate_left(link_t root);
static int find_recursive(link_t root, int item);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(int item, size_t size, link_t left, link_t right)
{
    link_t t = alloc(sizeof *t);
    t->item  = item;
    t->size  = size;
    t->left  = left;
    t->right = right;
    return t;
}

static void dellink(link_t *t)
{
    if (t == NULL || *t == NULL) return ;
    free(*t);
    *t = NULL;
}

T bst_init()
{
    T t = alloc(sizeof *t);
    t->root = null_link;

    return t;
};

void bst_finalize(T *t)
{
    if (t == NULL || *t == NULL) return ;
    postorder_visit((*t)->root, dellink);
    free(*t);
    *t = NULL;
}

static void postorder_visit(link_t root, void (*f)(link_t *))
{
    if (root == null_link || root == NULL) return ;

    postorder_visit(root->left, f);
    postorder_visit(root->right, f);
    f(&root);
}

void bst_insert_normal(T t, int item)
{
    t->root = insert_bottom(t->root, item);
}

static link_t insert_bottom(link_t root, int item)
{
    if (root == null_link || root == NULL)
        return newlink(item, 1, null_link, null_link);

    root->size++;
    if (item < root->item)
        root->left = insert_bottom(root->left, item);
    else {
        root->right = insert_bottom(root->right, item);
    }

    return root;
}

static int powerof2(size_t n)
{
    while (n != 2) {
        if (n % 2 != 0) return 0;
        n /= 2;
    }

    return 1;
}
void bst_insert_balance(T t, int item)
{
    t->root = insert_bottom(t->root, item);
    if (powerof2(t->root->size)) {
        t->root = balance_recursive(t->root);
    }
}

static link_t balance_recursive(link_t root)
{
    if (root->size < 2) return root;

    root = partition_recursive(root, root->size / 2);
    root->left = balance_recursive(root->left);
    root->right = balance_recursive(root->right);

    return root;
}


static link_t partition_recursive(link_t root, size_t k)
{
    if (root == null_link || root == NULL) return root;

    size_t cur = root->left->size;
    if (k < cur) {
        root->left = partition_recursive(root->left, k);
        root = rotate_right(root);
    }
    else if (k > cur) {
        root->right = partition_recursive(root->right, k - cur - 1);
        root = rotate_left(root);
    }

    return root;
}

static size_t count_size(link_t root)
{
    return root->left->size + root->right->size + 1;
}
static link_t rotate_right(link_t root)
{
    if (root == null_link) return root;

    link_t down = root->left;
    root->left = down->right;
    down->right = root;

    down->size = root->size;
    root->size = count_size(root);

    return down;
}

static link_t rotate_left(link_t root)
{
    if (root == null_link) return root;

    link_t down = root->right;
    root->right = down->left;
    down->left = root;

    down->size = root->size;
    root->size = count_size(root);

    return down;
}

static int find_recursive(link_t root, int item)
{
    if (root == null_link) return -1;

    if (item < root->item) {
        return find_recursive(root->left, item);
    }
    else if (item > root->item) {
        return find_recursive(root->right, item);
    }

    return 1;
}

int bst_find(T t, int item)
{
    return find_recursive(t->root, item);
}
