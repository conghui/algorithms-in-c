#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "btree.h"

#define item_t int
#define T btree_t
int count;

static void *alloc(size_t size);
static link_t newlink(item_t item, link_t l, link_t r);
static void dellink(link_t *l);
static void deltree(link_t *t);
static link_t _create_tree(char **str);
static void preorder(link_t root, void (*visit)(link_t));
static int external_node(const_link_t root);
static int internal_node(const_link_t root);
static int has_both_node(const_link_t root);
static int _special_node_cnt(link_t root);
void btree_finalize(T *t);
T btree_init(char *str);
void btree_preorder_traverse(T t, void (*visit)(link_t));
int btree_special_node_cnt(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(item_t item, link_t l, link_t r)
{
    link_t nl = alloc(sizeof * nl);
    nl->item  = item;
    nl->left  = l;
    nl->right = r;
    return nl;
}

static void dellink(link_t *l)
{
    free(*l);
    *l = NULL;
}

void btree_finalize(T *t)
{
    if (*t == NULL) {
        return ;
    }

    deltree(&(*t)->root);
    free(*t);
    *t = NULL;
}

static void deltree(link_t *t)
{
    if (*t == NULL) {
        return ;
    }

    if ((*t)->left != NULL) {
        deltree(&(*t)->left);
    }

    if ((*t)->right != NULL) {
        deltree(&(*t)->right);
    }

    dellink(t);
}


T btree_init(char *str)
{
    T t     = alloc(sizeof * t);
    t->root = _create_tree(&str);
    return t;
}

static link_t _create_tree(char **str)
{
    if (**str == '#') {
        return NULL;
    }

    item_t item = **str - '0';
    link_t root = newlink(item, NULL, NULL);
    (*str)++;
    root->left  = _create_tree(str);
    (*str)++;
    root->right = _create_tree(str);
    return root;
}

void btree_preorder_traverse(T t, void (*visit)(link_t))
{
    preorder(t->root, visit);
}

static void preorder(link_t root, void (*visit)(link_t))
{
    count++;

    if (root == NULL) {
        return;
    }

    visit(root);

    if (root->left) {
        preorder(root->left, visit);
    }

    if (root->right) {
        preorder(root->right, visit);
    }
}

static int external_node(const_link_t root)
{
    if (root == NULL) {
        return 0;
    }

    return root->left == NULL && root->right == NULL;
}

static int internal_node(const_link_t root)
{
    if (root == NULL) {
        return 0;
    }

    return root->left != NULL || root->right != NULL;
}

/* the node contains both external node and internal node */
static int has_both_node(const_link_t root)
{
    if (root == NULL) {
        return 0;
    }

    if ((external_node(root->left) && internal_node(root->right)) ||
        (external_node(root->right) && internal_node(root->left))) {
        return 1;
    }

    return 0;
}

static int _special_node_cnt(link_t root)
{
    count++;

    if (root == NULL) {
        return 0;
    }

    int leftcnt  = 0;
    int rightcnt = 0;
    int rootcnt = 0;

    if (root->left != NULL) {
        leftcnt = _special_node_cnt(root->left);
    }

    if (root->right != NULL) {
        rightcnt = _special_node_cnt(root->right);
    }

    rootcnt = has_both_node(root);

    if (rootcnt) {
        printf("%d ", root->item);
    }

    return leftcnt + rightcnt + rootcnt;
}

int btree_special_node_cnt(T t)
{
    return _special_node_cnt(t->root);
}
