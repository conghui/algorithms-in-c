#include <stdlib.h>
#include <assert.h>

#include "queue.h"

typedef struct T *T;

struct T {
    Item entry;
    T    next;
};

static T head;
static T tail;
static void *alloc(size_t size);
static T newnode(Item n, T next);
static void queue_push_ignore_new(Item n);
static void queue_push_item(Item n);
static void queue_push_del_old(Item n);
static T find(Item n, T *pprev, T *pcur);
static void remove(T prev, T cur);

void queue_push(Item n)
{
#if defined (DEL_OLD)
    queue_push_del_old(n);
#elif defined (IGNORE_NEW)
    queue_push_ignore_new(n);
#endif
}
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

void queue_init(void)
{
    head = tail = NULL;
}


static void queue_push_ignore_new(Item n)
{
    T prev;
    T cur;

    if (find(n, &prev, &cur)) {
        return ;    /* ignore the new item, just return */
    }

    queue_push_item(n);
}

static void queue_push_item(Item n)
{
    T nn = newnode(n, head);

    if (head == NULL) { /* the queue is empty */
        head = tail = nn;
    } else {
        head = nn;
    }
}

static void queue_push_del_old(Item n)
{
    T prev;
    T cur;

    if (find(n, &prev, &cur) != NULL) { /* item found */
        remove(prev, cur);
    }

    queue_push_item(n);
}

Item queue_pop()
{
    Item reval = head->entry;
    remove(NULL, head);
    return reval;
}

static T find(Item n, T *pprev, T *pcur)
{
    T prev;
    T cur;

    if (queue_empty()) {
        *pprev = *pcur = NULL;
        return NULL;
    }

    /* the queue is not empty */
    prev = NULL;
    cur  = head;

    for (; cur != NULL; prev = cur, cur = cur->next) {
        if (cur->entry == n) { /* find the item */
            *pprev = prev;
            *pcur  = cur;
            return cur;
        }
    }

    /* item not found */
    *pprev = NULL;
    *pcur = NULL;
    return NULL;
}

int queue_empty()
{
    return head == NULL && tail == NULL;
}

static void remove(T prev, T cur)
{
    T tmp = cur;

    if (cur == head && cur == tail) { /* only one item in the queue */
        head = tail = NULL;
    } else if (cur == head) { /* the head, but not the tail */
        head = head->next;
    } else if (cur == tail) { /* the tail, but not the head */
        tail = prev;
    } else { /* in the middle of the queue */
        prev->next = cur->next;
    }

    free(tmp);
}

void queue_finalize()
{
    while (!queue_empty()) {
        queue_pop();
    }
}
