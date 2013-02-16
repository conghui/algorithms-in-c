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

static int inner_node_cnt_array[BUFSIZ];

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

static int count_internal_node(link_t root)
{
    int nleft  = 0;
    int nright = 0;
    int nroot  = 0;
    int reval;
    count++;

    if (root == NULL) {
        return 0;
    }

    if ((reval = inner_node_cnt_array[root->item]) != 0) {
        return reval;
    }

    if (root->left) {
        nleft = count_internal_node(root->left);
    }

    if (root->right) {
        nright = count_internal_node(root->right);
    }

    nroot = internal_node(root);

    if (inner_node_cnt_array[root->item] == 0) {
        inner_node_cnt_array[root->item] = nroot;
    }

    return nleft + nright + nroot;
}

static int internal_length(link_t root, size_t nnode)
{
    if (nnode <= 1) {
        return 0;
    }

    int nleft = count_internal_node(root->left);
    int nright = count_internal_node(root->right);
    int nnleft  = 0;
    int nnright = 0;

    if (nleft > 1) {
        nnleft = internal_length(root->left, nleft);
    }

    if (nright > 1) {
        nnright = internal_length(root->right, nright);
    }

    return nnleft + nnright + nnode - 1;
}

int btree_internal_length(T t)
{
    size_t nnode = count_internal_node(t->root);
    return internal_length(t->root, nnode);
}
