#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "bst.h"

#define T bst_t

typedef struct node_t *link_t;

struct node_t {
    int key;
    size_t count;
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
static int null_key = INT_MIN;

static void *alloc(size_t size);
static link_t newlink(int key, size_t count, link_t left, link_t right);
static void dellink(link_t *t);
static void postorder_visit(link_t root, void (*f)(link_t *));
static link_t insert_top(link_t root, int key);
static size_t calcount(link_t root);
static link_t rotate_left(link_t root);
static link_t rotate_right(link_t root);
static link_t partition(link_t root, int k);
static link_t join_left_right(link_t a, link_t b);
static link_t delete_recursive(link_t root, int key);
static int select_recursive(link_t root, int k);
static link_t join_recursive(link_t a, link_t b);
static int height_recursive(link_t root);
T bst_init();
void bst_finalize(T *t);
void bst_insert(T t, int key);
void bst_delete(T t, int key);
int bst_select(T t, int k);
void bst_join(T t1, T t2);
int bst_height(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(int key, size_t count, link_t left, link_t right)
{
    link_t t = alloc(sizeof *t);
    t->key = key;
    t->count = count;
    t->left = left;
    t->right = right;

    return t;
}

static void dellink(link_t *t)
{
    if (t == NULL || *t == null_link) return ;
    free(*t);
    *t = null_link;
}

T bst_init()
{
    T t = alloc(sizeof *t);
    t->root = null_link;
    return t;
}

static void postorder_visit(link_t root, void (*f)(link_t *))
{
    if (root == null_link) return ;
    postorder_visit(root->left, f);
    postorder_visit(root->right, f);
    f(&root);
}

void bst_finalize(T *t)
{
   if (t == NULL || *t == NULL) return ;
   postorder_visit((*t)->root, dellink);
   free(*t);
   *t = NULL;
}

static link_t insert_top(link_t root, int key)
{
    if (root == null_link) return newlink(key, 1, null_link, null_link);

    root->count++;
    if (key < root->key) {
        root->left = insert_top(root->left, key);
        root = rotate_right(root);
    }
    else {
        root->right = insert_top(root->right, key);
        root = rotate_left(root);
    }

    return root;
}

static size_t calcount(link_t root)
{
    return 1 + root->left->count + root->right->count;
}

static link_t rotate_left(link_t root)
{
    link_t down = root->right;
    root->right = down->left;
    down->left = root;

    down->count = root->count;
    root->count = calcount(root);

    return down;
}

static link_t rotate_right(link_t root)
{
    link_t down = root->left;
    root->left = down->right;
    down->right = root;

    down->count = root->count;
    root->count = calcount(root);

    return down;
}

void bst_insert(T t, int key)
{
    t->root = insert_top(t->root, key);
}

static link_t partition(link_t root, int k)
{
    if (root == null_link) return null_link;

    int cur = root->left->count;
    if (k < cur) {
        root->left = partition(root->left, k);
        root = rotate_right(root);
    }
    else if (k > cur) {
        root->right = partition(root->right, k - cur - 1);
        root = rotate_left(root);
    }

    /* k == cur */
    return root;
}

static link_t join_left_right(link_t a, link_t b)
{
    if (a == null_link) return b;
    if (b == null_link) return a;

    b = partition(b, 0);
    b->left = a;

    return b;
}
static link_t delete_recursive(link_t root, int key)
{
    if (root == null_link) return null_link;

    root->count--;
    if (key < root->key) {
        root->left = delete_recursive(root->left, key);
    }
    else if (key > root->key) {
        root->right = delete_recursive(root->right, key);
    }
    else { /* key == root->key */
        link_t tmp = root;
        root = join_left_right(root->left, root->right);
        dellink(&tmp);
    }

    return root;
}
void bst_delete(T t, int key)
{
   t->root = delete_recursive(t->root, key);
}

/**
 * @brief select the kth smallest element from the tree
 *
 * @param t the tree handle
 * @param k the kth, count from 0
 *
 * @return the key of the kth element
 */
int bst_select(T t, int k)
{
    return select_recursive(t->root, k);
}

static int select_recursive(link_t root, int k)
{
    if (root == null_link) return null_key;
    int cur = root->left->count;

    if (k < cur) { /* we should find the key in the subtree */
        return select_recursive(root->left, k);
    }
    else if (k > cur) { /* we should find the key in the right subtree */
        return select_recursive(root->right, k - cur - 1);
    }
    else { /* k == cur */
        return root->key;
    }
}

/**
 * @brief join tree binary search tree, join t2 into j1
 *
 * @param t1 the first binary tree, and it will hold the result
 * @param t2 the second binary tree
 */
void bst_join(T t1, T t2)
{
    t1->root = join_recursive(t1->root, t2->root);
}

static link_t join_recursive(link_t a, link_t b)
{
    if (a == null_link) return b;
    if (b == null_link) return a;

    /* insert the root of 'b' into a by the 'insert at top' insertion,
     * then combine the left tree of 'a' and 'b' as the new left tree,
     * and the right tree of 'a' and 'b' as the new right tree*/
    a        = insert_top(a, b->key);
    a->left  = join_recursive(a->left, b->left);
    a->right = join_recursive(a->right, b->right);
    return a;
}

static int height_recursive(link_t root)
{
    if (root == null_link) return 0;

    int lh = 0;
    int rh = 0;
    lh = height_recursive(root->left) + 1;
    rh = height_recursive(root->right) + 1;
    return lh > rh ? lh : rh;
}

int bst_height(T t)
{
    return height_recursive(t->root) - 1;
}
