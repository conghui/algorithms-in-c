#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stack>

using namespace std;

#define T spt_t

typedef struct node_t *link_t;
typedef struct _T *T;
typedef char *item_t;

struct node_t
{
    item_t item;
    size_t size;
    link_t left;
    link_t right;
};

struct _T
{
    link_t root;
};

static struct node_t null_node = { NULL, 0, NULL, NULL};
static link_t null_link        = &null_node;
static void *alloc(size_t size);
link_t newlink(const item_t item, size_t size, link_t left, link_t right);
void dellink(link_t *t);
T spt_init();
void postorder_visit(link_t root, void (*f)(link_t *));
void spt_finalize(T *t);
int lt(item_t a, item_t b);
size_t fix_size(link_t root);
link_t rotate_left(link_t root);
link_t rotate_right(link_t root);
link_t splay_insert(link_t root, item_t item);
void spt_insert(T t, item_t item);
size_t getsize(link_t root);
link_t partition(link_t root, size_t k);
link_t join_left_right(link_t a, link_t b);
link_t erase_single(link_t root, item_t item, int *found);
void spt_erase(T t, item_t item);
size_t spt_size(T t);
void inorder_print(link_t root);
void spt_sort(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

link_t newlink(const item_t item, size_t size, link_t left, link_t right)
{
    link_t t = (link_t)alloc(sizeof *t);
    t->item  = (item_t)alloc(strlen(item) + 1);
    t->size  = size;
    t->left  = left;
    t->right = right;
    strcpy(t->item, item);
    return t;
}

void dellink(link_t *t)
{
    if (t == NULL || *t == NULL) return ;

    free((*t)->item);
    free(*t);
    *t = NULL;
}

T spt_init()
{
    T t = (T)alloc(sizeof *t);
    t->root = null_link;
    return t;
}

void postorder_visit(link_t root, void (*f)(link_t *))
{
    if (root == null_link || root == NULL) return ;

    postorder_visit(root->left, f);
    postorder_visit(root->right, f);
    f(&root);
}
void spt_finalize(T *t)
{
    if (t == NULL || *t == NULL) return ;
    postorder_visit((*t)->root, dellink);
    free(*t);
    *t = NULL;
}

int lt(item_t a, item_t b)
{
    for (; tolower(*a) == tolower(*b) && *a != '\0'; a++, b++) ;
    return tolower(*a) < tolower(*b);
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

link_t splay_insert(link_t root, item_t item)
{
    if (root == null_link)  {
        return newlink(item, 1, null_link, null_link);
    }

    root->size++;
    if (lt(item, root->item)) {
        if (root->left == null_link) {
            root->left = newlink(item, 1, null_link, null_link);
            root = rotate_right(root);
            return root;
        }
        root->left->size++;
        if (lt(item, root->left->item)) {
            root->left->left = splay_insert(root->left->left, item);
            /*root->left = rotate_right(root->left);*/
            root = rotate_right(root);
        } else {
            root->left->right = splay_insert(root->left->right, item);
            root->left = rotate_left(root->left);
        }

        return rotate_right(root);
    } else {
        if (root->right == null_link) {
            root->right = newlink(item, 1, null_link, null_link);
            return rotate_left(root);
        }
        root->right->size++;
        if (lt(item, root->right->item)) {
            root->right->left = splay_insert(root->right->left, item);
            root->right = rotate_right(root->right);
        } else {
            root->right->right = splay_insert(root->right->right, item);
            /*root->right = rotate_left(root->right);*/
            root = rotate_left(root);
        }

        return rotate_left(root);
    }
}

typedef struct 
{
    link_t root;
    int rotate_dir; /* rotate direction, 1 for left, 2 for right */
} stk_element_t;

//link_t splay_insert_nonrecursive(link_t root, item_t item)
//{
    //stack<stk_element_t> stk;
    //stk_element_t cur = {root, 0};
    //stk_element_t tmp;
    //stk.push(cur);

    //while (!stk.empty()) {
        //cur = stk.top(); stk.pop();
        //if (cur.root == null_link) {
            //return newlink(item, 1, null_link, null_link);
        //} 

        //if (cur.rotate_dir == 1) { [> rotate left <]
            //cur.root = rotate_left(cur.root);
        //} else if (cur.rotate_dir == 2) { [> rotate right <]
            //cur.root = rotate_right(cur.root);
        //}

        //cur.root->size++;
        //if (lt(item, cur.root->item)) {
            //if (cur.root->left == null_link) {
                //cur.root->left = newlink(item, 1, null_link, null_link);
                //return rotate_right(cur.root);
            //}
            //cur.root->size++;
            //if (lt(item, cur.root->left->item)) {
                //tmp = {cur.root->left->left, 2};
                //stk.push(tmp);
            //} else {
                //tmp = {cur.root->left->right, 1};
                //stk.push(tmp);
            //}
        //}
    //}
//}
void spt_insert(T t, item_t item)
{
    t->root = splay_insert(t->root, item);
}

size_t getsize(link_t root)
{
    return root->size;
}

link_t partition(link_t root, size_t k)
{
    if (root == null_link || root == NULL) return root;

    size_t cur = getsize(root->left);
    if (k < cur) {
        root->left = partition(root->left, k);
        root = rotate_right(root);
    } else if (k > cur) {
        root->right = partition(root->right, k - cur - 1);
        root = rotate_left(root);
    }

    return root;
}
link_t join_left_right(link_t a, link_t b)
{
    if (b == null_link) return a;
    b = partition(b, 0);
    b->left = a;
    b->size = fix_size(b);
    return b;
}

link_t erase_single(link_t root, item_t item, int *found)
{
    if (root == null_link || root == NULL) return root;

    if (lt(item, root->item)) {
        root->left = erase_single(root->left, item, found);
    } else if (lt(root->item, item)) {
        root->right = erase_single(root->right, item, found);
    } else {
        link_t tmp = root;
        root = join_left_right(root->left, root->right);
        dellink(&tmp);
        *found = 1;
    }
    
    if (*found) root->size--;
    return root;
}

void spt_erase(T t, item_t item)
{
    int found = 0;
    t->root = erase_single(t->root, item, &found);
}

size_t spt_size(T t)
{
    return getsize(t->root);
}

void inorder_print(link_t root)
{
    if (root == null_link || root == NULL) return ;
    inorder_print(root->left);
    printf("item:%10s, size:%2d\n", root->item, root->size);
    inorder_print(root->right);
}

void spt_sort(T t)
{
    inorder_print(t->root);
}
#undef T

int main(void)
{
    int n, m;

    while (scanf("%d%d", &n, &m) == 2 && n != 0) {
        spt_t spt = spt_init();
        char buf[BUFSIZ];
        int i;
        for (i = 0; i < n; i++) {
            assert(scanf("%s", buf) == 1);
            spt_insert(spt, buf);
        }

        /*spt_sort(spt); putchar('\n');*/
        for (i = 0; i < m; i++) {
            assert(scanf("%s", buf) == 1);
            spt_erase(spt, buf);
            /*spt_sort(spt); putchar('\n');*/
        }

        printf("%d\n", spt_size(spt));
        spt_finalize(&spt);
    }
    return 0;
}
