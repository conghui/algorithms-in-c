#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stack>

#include "btree.h"

using namespace std;

static void *alloc(size_t size);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

link_t newlink(item_t item, link_t l, link_t r)
{
    link_t nl = (link_t)alloc(sizeof * l);
    nl->item  = item;
    nl->l     = l;
    nl->r     = r;
    return nl;
}

void dellink(link_t *l)
{
    free(*l);
    *l = NULL;
}

link_t mytree()
{
    link_t a, b, c, d, e, f, g, h;
    a = newlink('A', NULL, NULL);
    c = newlink('C', NULL, NULL);
    b = newlink('B', a, c);
    d = newlink('D', b, NULL);
    g = newlink('G', NULL, NULL);
    f = newlink('F', NULL, g);
    h = newlink('H', f, NULL);
    e = newlink('E', d, h);
    return e;
}

void preorder1(link_t root, void (*visit)(link_t))
{
    if (root == NULL) {
        return ;
    }

    visit(root);
    preorder1(root->l, visit);
    preorder1(root->r, visit);
}

void preorder2(link_t root, void (*visit)(link_t))
{
    while (1) {
        if (root == NULL) {
            return ;
        }

        visit(root);
        preorder2(root->l, visit);
        root = root->r;
    }
}

void preorder3(link_t root, void (*visit)(link_t))
{
    while (root != NULL) {
        visit(root);
        preorder3(root->l, visit);
        root = root->r;
    }
}

void preorder4(link_t root, void (*visit)(link_t))
{
    stack<link_t> stk;

    while (root != NULL || !stk.empty())  {
        if (root == NULL) {
            root = stk.top();
            stk.pop();
            root = root->r;
        }

        if (root != NULL) {
            visit(root);
            stk.push(root);
            root = root->l;
        }
    }
}

void preorder_traverse(link_t root, void (*visit)(link_t))
{
    stack<link_t> stk;

    while (root != NULL || !stk.empty()) {
        if (root == NULL) {
            root = stk.top();
            stk.pop();
        }

        visit(root);

        if (root->r != NULL) {
            stk.push(root->r);
        }

        root = root->l;
    }
}

void inorder1(link_t root, void (*visit)(link_t))
{
    if (root == NULL) {
        return ;
    }

    inorder1(root->l, visit);
    visit(root);
    inorder1(root->r, visit);
}

void inorder2(link_t root, void (*visit)(link_t))
{
    while (root != NULL) {
        inorder1(root->l, visit);
        visit(root);
        root = root->r;
    }
}

void inorder3(link_t root, void (*visit)(link_t))
{
    stack<link_t> stk;

    while (root != NULL || !stk.empty()) {
        /* when to pop */
        if (root == NULL) {
            root = stk.top();
            stk.pop();
            visit(root);
            root = root->r;
        }

        if (root != NULL) {
            stk.push(root);
            root = root->l;
        }
    }
}

void inorder_traverse(link_t root, void (*visit)(link_t))
{
    stack<link_t> stk;

    while (root != NULL || !stk.empty()) {
        if (root == NULL) {
            root = stk.top();
            stk.pop();
            visit(root);
            root = root->r;
        }

        if (root != NULL) {
            stk.push(root);
            root = root->l;
        }
    }
}

void postorder1(link_t root, void (*visit)(link_t))
{
    if (root != NULL) {
        postorder1(root->l, visit);
        postorder1(root->r, visit);
        visit(root);
    }
}

void postorder_traverse(link_t root, void (*visit)(link_t))
{
    stack<link_t> stk;

    while (root != NULL || !stk.empty()) {
        if (root == NULL) {
            while (!stk.empty() && root == stk.top()->r) {
                root = stk.top();
                stk.pop();
                visit(root);
            }

            root = stk.empty() ? NULL : stk.top()->r;
        }

        if (root != NULL) {
            stk.push(root);
            root = root->l;
        }
    }
}
