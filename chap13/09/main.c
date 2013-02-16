#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define T bst_t

typedef char *item_t;
typedef struct T *T;
typedef struct node_t *link_t;

struct node_t
{
    char   *name;
    size_t  size;
    link_t  left;
    link_t  right;
};

struct T
{
    link_t root;
};

static struct node_t null_node = {
    NULL,
    0,
    NULL,
    NULL
};

static link_t null_link = &null_node;
static void *alloc(size_t size);
static link_t newlink(const char *name, size_t size, link_t left, link_t right);
static void dellink(link_t *t);
static void postorder_visit(link_t root, void (*f)(link_t *));
static int lt(item_t a, item_t b);
static int eq(item_t a, item_t b);
static int gt(item_t a, item_t b);
static size_t fix_size(link_t root);
static link_t rotate_left(link_t root);
static link_t rotate_right(link_t root);
static link_t partition(link_t root, size_t k);
static link_t join_left_right(link_t a, link_t b);
static link_t erase_single(link_t root, item_t name, size_t *count, size_t *found);
static void inorder_print(link_t root);
T bst_init();
void bst_finalize(T *t);
link_t insert_top(link_t root, item_t name);
link_t insert_bottom(link_t root, item_t name);
link_t insert_random(link_t root, item_t name);
void bst_insert(T t, item_t name);
size_t bst_erase(T t, item_t name);
size_t size_recursive(link_t root);
size_t bst_size(T t);
void bst_sort(T t);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static link_t newlink(const char *name, size_t size, link_t left, link_t right)
{
    link_t t = alloc(sizeof *t);
    t->name  = alloc(strlen(name) + 1);
    t->size  = size;
    t->left  = left;
    t->right = right;
    strcpy(t->name, name);

    return t;
}

static void dellink(link_t *t)
{
    if (t == NULL || *t == NULL) return ;
    if ((*t)->name != NULL) free((*t)->name);
    free(*t);
    *t = NULL;
}

T bst_init()
{
    T t = alloc(sizeof *t);
    t->root = null_link;
    return t;
}

static void postorder_visit(link_t root, void (*f)(link_t *))
{
    if (root == null_link || root == NULL) return ;
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

static int lt(item_t a, item_t b)
{
    for (; tolower(*a) == tolower(*b); a++, b++) {
        if (*a == '\0') break;
    }

    return tolower(*a) < tolower(*b);
}

static int eq(item_t a, item_t b)
{
    return !lt(a, b) && !lt(b, a);
}

static int gt(item_t a, item_t b)
{
    return !lt(a, b) && !eq(a, b);
}

link_t insert_top(link_t root, item_t name)
{
    if (root == null_link || root == NULL) {
        return newlink(name, 1, null_link, null_link);
    }

    root->size++;
    if (lt(name, root->name)) {
        root->left = insert_top(root->left, name);
        root = rotate_right(root);
    } else {
        root->right = insert_top(root->right, name);
        root = rotate_left(root);
    }

    return root;
}

link_t insert_bottom(link_t root, item_t name)
{
    if (root == null_link || root == NULL) {
        return newlink(name, 1, null_link, null_link);
    }

    root->size++;
    if (lt(name, root->name)) {
        root->left = insert_bottom(root->left, name);
    }
    else {
        root->right = insert_bottom(root->right, name);
    }

    return root;
}

link_t insert_random(link_t root, item_t name)
{
    if (root == null_link || root == NULL) {
        return newlink(name, 1, null_link, null_link);
    }

    if ((size_t)rand() < RAND_MAX / root->size) {
        return insert_top(root, name);
    }
    
    root->size++;
    if (lt(name, root->name)) {
        root->left = insert_random(root->left, name);
    } else {
        root->right = insert_random(root->right, name);
    }

    return root;
}
void bst_insert(T t, item_t name)
{
    t->root = insert_bottom(t->root, name);
    /*t->root = insert_top(t->root, name);*/
    /*t->root = insert_random(t->root, name);*/
}

static size_t fix_size(link_t root)
{
    return size_recursive(root->left) + size_recursive(root->right) + 1;
    /*return root->left->size + root->right->size + 1;*/
}

static link_t rotate_left(link_t root)
{
    link_t down = root->right;
    root->right = down->left;
    down->left = root;

    /*down->size = root->size;*/
    /*root->size = fix_size(root);*/

    return down;
}

static link_t rotate_right(link_t root)
{
    link_t down = root->left;
    root->left = down->right;
    down->right = root;

    /*down->size = root->size;*/
    /*root->size = fix_size(root);*/

    return down;
}
static link_t partition(link_t root, size_t k)
{
    /*size_t cur = root->left->size;*/
    size_t cur = size_recursive(root->left);
    if (k < cur) {
        root->left = partition(root->left, k);
        root = rotate_right(root);
    }
    else if (k > cur) {
        root->right = partition(root->right, k - cur - 1);
        root = rotate_left(root);
    }

    return root;
}
static link_t join_left_right(link_t a, link_t b)
{
    if (b == null_link || b == NULL) return a;

    /* b is not empty */
    b = partition(b, 0);
    b->left = a;
    /*b->size = fix_size(b);*/
    return b;
}

static link_t erase_single(link_t root, item_t name, size_t *count, size_t *found)
{
    if (root == null_link || root == NULL) {
        *count += 0;
        return root;
    }

    size_t cur, left, right;
    cur = left = right = 0;

    if (lt(name, root->name)) {
        root->left = erase_single(root->left, name, count, found);
    }
    else if (gt(name, root->name)) {
        root->right = erase_single(root->right, name, count, found);
    }
    else {
        link_t tmp = root;
        root = join_left_right(root->left, root->right);
        dellink(&tmp);
        cur = 1;
        /*root->size++;*/
        *found = 1;
    }

    /*if (*found) root->size--;*/
    *count += cur + left + right;

    return root;
}

size_t bst_erase(T t, item_t name)
{
    size_t count = 0;
    size_t found = 0;
    t->root =  erase_single(t->root, name, &count, &found);
    return count;
}

size_t size_recursive(link_t root)
{
    if (root == null_link || root == NULL) return 0;

    return size_recursive(root->left) + size_recursive(root->right) + 1;
}
size_t bst_size(T t)
{
    /*return t->root->size;*/
    return size_recursive(t->root);
}

static void inorder_print(link_t root)
{
    if (root == null_link) return ;

    inorder_print(root->left);
    printf("size:%d, %s\n", size_recursive(root), root->name);
    inorder_print(root->right);
}

void bst_sort(T t)
{
    inorder_print(t->root);
}
#undef T
int main(void)
{
    int n, m;

    while (scanf("%d%d", &n, &m) == 2 && n != 0) {
        char buf[BUFSIZ];
        int i;
        bst_t bst;

        bst = bst_init();
        for (i = 0; i < n; i++) {
            assert(scanf("%s", buf) == 1);
            bst_insert(bst, buf);
        }

        /*bst_sort(bst);*/
        for (i = 0; i < m; i++) {
            assert(scanf("%s", buf) == 1);
            bst_erase(bst, buf);
            /*putchar('\n'); bst_sort(bst);*/
        }

        printf("%d\n", bst_size(bst));
        bst_finalize(&bst);
    }
    return 0;
}
