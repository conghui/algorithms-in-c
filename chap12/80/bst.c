#include <stdio.h>
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

struct _T {
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
static link_t newlink(int key, size_t count, link_t left, link_t right);
static void dellink(link_t *t);
static void postorder_visit(link_t root, void (*f)(link_t *));
static link_t insert_top(link_t root, int key);
static link_t rotate_right(link_t root);
static link_t rotate_left(link_t root);
static void print(link_t *t);
static void inorder_visit(link_t root, void (*f)(link_t *));
static link_t delete_recursive(link_t root, int key);
static link_t join_lr(link_t a, link_t b);
static link_t join_2_tree(link_t a, link_t b);
static int select_no_recursive(link_t root, int k);
static void delete_non_recursive(T t, int key);
T bst_init();
void bst_finalize(T *t);
void bst_insert(T t, int key);
void bst_sort(T t);
int select_recursive(link_t root, int k);
int bst_select(T t, int k);
link_t partition_recursive(link_t root, int k);
void bst_partition(T t, int k);
void bst_delete(T t, int key);
int bst_empty(T t);
void bst_join(T t1, T t2);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(int key, size_t count, link_t left, link_t right)
{
    link_t t = alloc(sizeof *t);
    t->key   = key;
    t->count = count;
    t->left  = left;
    t->right = right;

    return t;
}

static void dellink(link_t *t)
{
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
    postorder_visit((*t)->root, dellink);
    free(*t);
    *t = NULL;
}

void bst_insert(T t, int key)
{
    t->root = insert_top(t->root, key);
}

static link_t insert_top(link_t root, int key)
{
    if (root == null_link) return newlink(key, 1, null_link, null_link);

    /* as we insert an item, the count of current should increase by one */
    root->count++;
    if (key < root->key) { /* we should insert the key at the left subtree */
        root->left = insert_top(root->left, key);
        /* the nwe should move the root of left subtree as the root of the
         * current tree, that is, we should perform a rotate right action on the
         * current node.
         * */
        root = rotate_right(root);
    }
    else { /* we should insert the key at the right subtree */
        root->right = insert_top(root->right, key);
        root = rotate_left(root);
    }

    return root;
}

static link_t rotate_right(link_t root)
{
    link_t down = root->left;
    root->left = down->right;
    down->right = root;

    /* as we maintain a counter in each node, so we should change the value of
     * variable count in both 'down' and 'root' */
    down->count = root->count; /* 'down' become the current root */
    root->count = root->right->count + root->left->count + 1;

    return down;
}

static link_t rotate_left(link_t root)
{
    link_t down = root->right;
    root->right = down->left;
    down->left = root;

    down->count = root->count;
    root->count = root->left->count + root->right->count + 1;

    return down;
}

static void print(link_t *t)
{
    printf("key:%4d,   count:%3d\n", (*t)->key, (*t)->count);
}

static void inorder_visit(link_t root, void (*f)(link_t *))
{
    if (root == null_link) {
        return ;
    }

    inorder_visit(root->left, f);
    f(&root);
    inorder_visit(root->right, f);
}
void bst_sort(T t)
{
    inorder_visit(t->root, print);
}

/**
 * @brief select the kth smallest element from the tree
 *
 * k is from 0 to n - 1, which start to count from 0
 *
 * @param t the binary search tree
 * @param k the kth
 *
 * @return the key of the kth smallest element
 */
int select_recursive(link_t root, int k)
{
    int cur = root->left->count;

    if (k < cur) return select_recursive(root->left, k);
    if (k > cur) return select_recursive(root->right, k - cur - 1);

    /* k == cur */
    return root->key;
}

int bst_select(T t, int k)
{
    /*return select_recursive(t->root, k);*/
    return select_no_recursive(t->root, k);
}

link_t partition_recursive(link_t root, int k)
{
    int cur = root->left->count;

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

void bst_partition(T t, int k)
{
    t->root = partition_recursive(t->root, k);
}

/* we need to perform more action such as delete and join two BST */

static link_t delete_recursive_all(link_t root, int key)
{
    if (root == null_link) return null_link;

    root->left = delete_recursive(root->left, key);
    root->right = delete_recursive(root->right, key);
    if (key == root->key) {
        link_t tmp = root;
        root = join_lr(root->left, root->right);
        dellink(&tmp);
    }

    return root;

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
        root = join_lr(root->left, root->right);
        dellink(&tmp);
    }

    return root;
}

static link_t join_lr(link_t a, link_t b)
{
    if (b == null_link) return a;
    b = partition_recursive(b, 0);
    b->left = a;
    b->count = b->left->count + b->right->count + 1;
    return b;
}

void bst_delete(T t, int key)
{
    t->root = delete_recursive(t->root, key);
    /*delete_non_recursive(t, key);*/
}

int bst_empty(T t)
{
    return t->root == null_link;
}

static link_t join_2_tree(link_t a, link_t b)
{
    if (a == null_link) return b;
    if (b == null_link) return a;

    b        = insert_top(b, a->key);
    b->left  = join_2_tree(a->left, b->left);
    b->right = join_2_tree(a->right, b->right);
    b->count = b->left->count + b->right->count + 1;
    dellink(&a);
    return b;
}

void bst_join(T t1, T t2)
{
    t1->root = join_2_tree(t2->root, t1->root);
    t2->root = null_link;
}

static int select_no_recursive(link_t root, int k)
{
    int cur;
    while ((cur = root->left->count) != k) {
        if (k < cur) {
            root = root->left;
        }
        else {
            root = root->right;
            k = k - cur - 1;
        }
    }

    return root->key;
}

static void delete_non_recursive(T t, int key)
{
    link_t *cur = &t->root;
    while (key != (*cur)->key) {
        if (key < (*cur)->key) {
            cur = &(*cur)->left;
        }
        else {
            cur = &(*cur)->right;
        }
    }

    if (*cur == null_link) return ;

    /* we found the item to be delete */
    link_t tmp = (*cur);
    *cur = join_lr((*cur)->left, (*cur)->right);
    dellink(&tmp);
}
