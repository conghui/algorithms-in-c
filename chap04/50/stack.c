#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct T *T;

struct T {
    Item entry;
    T    next;
};

static T head = NULL;

static T find(Item n, T *pprev, T *pcur);
static void *alloc(size_t size);
static T newnode(Item n, T next);
static void stack_push_ignore_new(Item n);
static void stack_push_ignore_old(Item n);
static T find(Item n, T *pprev, T *pcur);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static T newnode(Item n, T next)
{
    T nn      = alloc(sizeof * nn);
    nn->entry = n;
    nn->next  = next;
    return nn;
}

static void stack_push_ignore_new(Item n)
{
    T cur;
    T prev;

    if ((cur = find(n, &prev, &cur)) != NULL) { /* the element exist */
        /* ignore the new element, just return */
        return;
    }

    /* element not exist, add the element to the stack */
    head = newnode(n, head);
}

static void stack_push_ignore_old(Item n)
{
    T cur;
    T prev;
    T tmp;

    if ((cur = find(n, &prev, &cur)) != NULL) { /* the element exist */
        /* ignore the old element, just remove it */
        tmp  = cur;

        if (tmp == head) { /* the found element is head */
            head = head->next;
        } else {
            prev->next = cur->next;
        }

        free(tmp);
    }

    head = newnode(n, head);
}

void stack_push(Item n)
{
#if defined (IGNORE_OLD)
    stack_push_ignore_old(n);
#elif defined (IGNORE_NEW)
    stack_push_ignore_new(n);
#endif
}

Item stack_pop()
{
    T tmp;
    Item reval;
    assert(!stack_empty());
    tmp  = head;
    reval = tmp->entry;
    head = head->next;
    free(tmp);
    return reval;
}

static T find(Item n, T *pprev, T *pcur)
{
    T cur;
    T prev;

    if (stack_empty()) { /* the stack is empty */
        *pprev = NULL;
        *pcur  = NULL;
        return NULL;
    }

    prev = NULL;

    for (cur = head; cur != NULL; prev = cur, cur = cur->next) {
        if (cur->entry == n) {
            *pprev = prev;
            *pcur  = cur;
            return cur;
        }
    }

    /* not found */
    *pprev = NULL;
    *pcur = NULL;
    return NULL;
}

int stack_empty()
{
    return head == NULL;
}
