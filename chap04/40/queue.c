#include <stdlib.h>
#include <assert.h>

#include "queue.h"

#define T link_t
typedef struct T *T;

struct T {
    Item entry;
    T    next;
};

static T head = NULL;
static T tail = NULL;

static T newnode(Item n, T next);
static void *alloc(size_t size);

int queue_empty()
{
    return head == NULL && tail == NULL;
}

static T newnode(Item n, T next)
{
    T nn      = alloc(sizeof * nn);
    nn->entry = n;
    nn->next  = next;
    return nn;
}

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

void queue_push(Item n)
{
    if (head == NULL) { /* the queue is empty */
        head       = tail = newnode(n, NULL);
        head->next = head;
        return ;
    } else {
        T nn       = newnode(n , tail->next);
        tail->next = nn;
        tail       = nn;
        return ;
    }
}

Item queue_pop()
{
    T   tmp;
    Item rt;
    assert(!queue_empty());

    if (head->next == head) { /* the last element in the queue */
        tmp  = head;
        rt   = head->entry;
        head = NULL;
        tail = NULL;
    } else {
        tmp = head;
        rt  = head->entry;
        head = head->next;
        tail->next = head;
    }

    free(tmp);
    return rt;
}
