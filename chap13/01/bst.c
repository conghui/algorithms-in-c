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
    int item;
    link_t left;
    link_t right;
};

struct T
{
    link_t root;
};

static struct node_t null_node = {0, NULL, NULL};
static link_t null_link        = &null_node;
static void *alloc(size_t size);
static link_t newlink(int item, link_t left, link_t right);
static void dellink(link_t *t);
static void postorder_visit(link_t root, void (*f)(link_t *));
static link_t insert_bottom(link_t root, int item);
static int size_recursive(link_t root);
static link_t partition_left(link_t root);
static link_t partition_right(link_t root);
static link_t partition_recursive(link_t root, int k);
static link_t balance_recursive(link_t root);
static void inorder_recursive_print(link_t root);
T bst_init();
void bst_finalize(T *t);
void bst_insert(T t, int item);
int bst_size(T t);
void bst_balance(T t);
void bst_sort(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(int item, link_t left, link_t right)
{
    link_t t = alloc(sizeof *t);
    t->item  = item;
    t->left  = left;
    t->right = right;

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
    t->root = null_link;

    return t;
}

void bst_finalize(T *t)
{
    if (t == NULL || *t == NULL || (*t)->root == null_link) return ;
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

static link_t insert_bottom(link_t root, int item)
{
    if (root == null_link) return newlink(item, null_link, null_link);

    if (item < root->item) {
        root->left = insert_bottom(root->left, item);
    }
    else {
        root->right = insert_bottom(root->right, item);
    }

    return root;
}

void bst_insert(T t, int item)
{
    t->root = insert_bottom(t->root, item);
}

static int size_recursive(link_t root)
{
    if (root == null_link) return 0;

    int lsize = size_recursive(root->left);
    int rsize = size_recursive(root->right);
    return lsize + rsize + 1;
}

int bst_size(T t)
{
    return size_recursive(t->root);
}

static link_t partition_left(link_t root)
{
    link_t down = root->right;
    root->right = down->left;
    down->left = root;
    return down;
}

static link_t partition_right(link_t root)
{
    link_t down = root->left;
    root->left = down->right;
    down->right = root;

    return down;
}
static link_t partition_recursive(link_t root, int k)
{
    if (root == null_link) return NULL;

    int cur = size_recursive(root->left);
    if (k < cur) {
        root->left = partition_recursive(root->left, k);
        root = partition_right(root);
    }
    else if (k > cur) {
        root->right = partition_recursive(root->right, k - cur - 1);
        root = partition_left(root);
    }
    return root;
}
static link_t balance_recursive(link_t root)
{
    if (size_recursive(root) < 2) return root;

    root = partition_recursive(root, size_recursive(root) / 2);
    root->left = balance_recursive(root->left);
    root->right = balance_recursive(root->right);

    return root;
}
void bst_balance(T t)
{
    t->root = balance_recursive(t->root);
}

static void inorder_recursive_print(link_t root)
{
    if (root == null_link) return ;

    inorder_recursive_print(root->left);
    printf("size:%2d item:%3d\n", size_recursive(root), root->item);
    inorder_recursive_print(root->right);
}

void bst_sort(T t)
{
    inorder_recursive_print(t->root);
}
