#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "rbt.h"

#define T rbt_t

typedef struct node_t *link_t;
struct node_t
{
    int    item;
    size_t size;
    int    red;
    link_t left;
    link_t right;
};

struct _T
{
    link_t root;
};

static struct node_t null_node = {
    0,
    0,
    0,
    NULL,
    NULL
};

static link_t null_link = &null_node;
void *alloc(size_t size);
link_t newlink(item_t item, size_t size, int red, link_t left, link_t right);
void dellink(link_t *t);
T rbt_init();
int lt(item_t a, item_t b);
size_t fix_size(link_t root);
link_t rotate_left(link_t root);
link_t rotate_right(link_t root);
link_t red_black_insert(link_t root, item_t item, int swap);
void rbt_insert(T t, item_t item);

void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

link_t newlink(item_t item, size_t size, int red, link_t left, link_t right)
{
    link_t t = alloc(sizeof *t);
    t->item  = item;
    t->size  = size;
    t->red   = red;
    t->left  = left;
    t->right = right;

    return t;
}

void dellink(link_t *t)
{
    if (t == NULL || *t == NULL) return;
    free(*t);
    *t = NULL;
}

T rbt_init()
{
    T t = alloc(sizeof *t);
    t->root = null_link;
    return t;
}

int lt(item_t a, item_t b)
{
    return a < b;
}

size_t fix_size(link_t root)
{
    return root->left->size + root->right->size + 1;
}
link_t rotate_left(link_t root)
{
    link_t down = root->right;
    root->right = down->left;
    down->left  = root;

    down->size = root->size;
    root->size = fix_size(root);

    return down;
}

link_t rotate_right(link_t root)
{
    link_t down = root->left;
    root->left  = down->right;
    down->right = root;

    down->size = root->size;
    root->size = fix_size(root);

    return down;
}
link_t red_black_insert(link_t root, item_t item, int swap)
{
    if (root == null_link) return newlink(item, 1, 1, null_link, null_link);

    /* check for the 4-node down throught the search path */
    if (root->left->red && root->right->red) { /* 4-node */
        /* combine the current node with its parent */
        root->red        = 1; 

        /* make its children as 2-node */
        root->left->red  = 0;
        root->right->red = 0;
    }
    if (lt(item, root->item)) {
        root->left = red_black_insert(root->left, item, 0);

        /* root->red: the root is 3-node */
        if (root->red && root->left->red && swap) {
            /* when the predicate evaluate true, the shape of the tree is
             *           +                      
             *            +
             *             +
             *              +
             *             +  
             *           +
             *         *   
             * as swap is 1, so the previous insertion is from the right 
             * of the parent, and the current insertion is from the left
             * of the current node, thus the newly inserted key is between 
             * the first key and the last key in the 3-node
             */
            root = rotate_right(root);
        }
        if (root->left->red && root->left->left->red) {
            /* the newly inserted key is the smallest key in the 3-node */
            root = rotate_right(root);
            root->red = 0;
            root->right->red = 1;
        }
    } else {
        root->right = red_black_insert(root->right, item, 1);
        if (root->red && root->right->red && !swap) {
            root = rotate_left(root);
        }
        if (root->right->red && root->right->right->red) {
            root = rotate_left(root);
            root->red = 0;
            root->left->red = 1;
        }
    }

    root->size = fix_size(root);
    return root;
}
void rbt_insert(T t, item_t item)
{
    t->root = red_black_insert(t->root, item, 0);
    t->root->red = 0;
}
