#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "queue.h"

typedef struct T *T;
typedef const struct T *CT;

struct T {
    Item entry;
    T    prev;
    T    next;
};

static T       head;      /* points to the head of the list    */
static T       tail;      /* points to the tail of the list    */
static T      *exist;     /* points to the dymanic array       */
static size_t  maxsize;   /* max size of the array             */
static size_t  count;     /* current # of element in the array */
static void *array_alloc(size_t n, size_t size);
static void *alloc(size_t size);
static T newnode(Item n, T prev, T next);
static void insert_back(Item n);
static int find_idx(Item n);
static void delete(Item n);

static void *array_alloc(size_t n, size_t size)
{
    void *p = calloc(n, size);
    assert(p);
    return p;
}

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static T newnode(Item n, T prev, T next)
{
    T nn = alloc(sizeof * nn);
    nn->entry = n;
    nn->next  = next;
    nn->prev  = prev;
    return nn;
}

/* init the queue, with the max # of element in the queue */
void queue_init(size_t n)
{
    head    = NULL;
    tail    = NULL;
    maxsize = n;
    count   = 0;
    exist   = array_alloc(n, sizeof * exist);
}

int queue_full()
{
    return count == maxsize;
}

int queue_empty()
{
    return count == 0;
}

void queue_push(Item n)
{
    assert(!queue_full());
    delete(n);
    insert_back(n);
}

Item queue_pop()
{
    Item reval = head->entry;
    assert(!queue_empty());
    delete(head->entry);
    return reval;
}

static void insert_back(Item n)
{
    T nn;
    assert(!queue_full());

    if (queue_empty()) { /* empty list */
        nn = newnode(n, NULL, NULL);
        head     = tail = nn;
        exist[n] = nn;  /* register it */
        count++;
        return ;
    }

    /* the list is not empty */
    nn         = newnode(n, tail, NULL);
    tail->next = nn;
    tail       = nn;
    exist[n]   = nn;    /* register it */
    count++;
}
/**
 * @brief find if the element n is in the queue
 *
 * @param n the element to be found
 *
 * @return the index of the element in the array if found, -1 if not found
 */
static int find_idx(Item n)
{
    if (exist[n] != NULL) { /* found the element */
        return n;
    } else { /* element not found */
        return -1;
    }
}

/**
 * @brief delete the element
 *
 * @param n
 */
static void delete(Item n)
{
    int idx;
    T tmp;

    if ((idx = find_idx(n)) == -1) {  /* the element not exist        */
        return ;
    }

    tmp = exist[idx];

    if (tmp == head && tmp == tail) { /* the only element in the list */
        head = tail = NULL;
    } else if (tmp == head) {         /* the head, but not the tail   */
        head       = tmp->next;
        head->prev = NULL;
    } else if (tmp == tail) {         /* the tail, but not the head   */
        tail       = tmp->prev;
        tail->next = NULL;
    } else {                          /* in the middle of the list    */
        tmp->prev->next = tmp->next;
    }

    exist[idx] = NULL;                /* un-register it               */
    free(tmp);
    count--;
}

void queue_finalize()
{
    while (!queue_empty()) {
        queue_pop();
    }

    free(exist);
}
