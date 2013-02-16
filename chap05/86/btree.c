#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "btree.h"

#define T btree_t
#define item_t int
static void *alloc(size_t size);
static size_t _leaf_cnt(const_link_t root);
static int has_child(const_link_t root);
static void _del_tree(link_t *root);
link_t newlink(item_t item, link_t left, link_t right);
void dellink(link_t *l);
T btree_init();
size_t btree_leaf_count(T t);
void btree_finalize(T *t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

link_t newlink(item_t item, link_t left, link_t right)
{
    link_t nl = alloc(sizeof * nl);
    nl->item  = item;
    nl->left  = left;
    nl->right = right;
    return nl;
}

void dellink(link_t *l)
{
    free(*l);
    *l = NULL;
}

T btree_init()
{
    T t = alloc(sizeof * t);
    link_t a, b, c, d, e, f, g, h;
    a = newlink('A', NULL, NULL);
    c = newlink('C', NULL, NULL);
    b = newlink('B', a, c);
    d = newlink('D', b, NULL);
    g = newlink('G', NULL, NULL);
    f = newlink('F', NULL, g);
    h = newlink('H', f, NULL);
    e = newlink('E', d, h);
    t->root = e;
    return t;
}


size_t btree_leaf_count(T t)
{
    return _leaf_cnt(t->root);
}

static size_t _leaf_cnt(const_link_t root)
{
    if (root == NULL) {
        return 0;
    } else if (!has_child(root)) {
        printf("%c ", root->item);
        return 1;
    }

    return _leaf_cnt(root->left) + _leaf_cnt(root->right);
}

static int has_child(const_link_t root)
{
    return root->left || root->right;
}

void btree_finalize(T *t)
{
    _del_tree(&(*t)->root);
    free(*t);
    *t = NULL;
}

static void _del_tree(link_t *root)
{
    if (*root == NULL) {
        return ;
    }

    _del_tree(&(*root)->left);
    _del_tree(&(*root)->right);
    dellink(root);
}
