#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

static Item   *content;
static size_t maxsize;   /* max size of the array                      */
static size_t headidx;   /* points to the first element                */
static size_t tailidx;   /* points to the next element of last element */
static size_t count;     /* # of elements in the queue                 */
static void *aalloc(size_t n, size_t size);
static void queue_push_del_old(Item n);
static void queue_push_ignore_new(Item n);
static int find(Item n);
static void delete(Item n);
void queue_init(size_t n);
int queue_empty();
void queue_push(Item n);
Item queue_pop();
void queue_finalize();

static void *aalloc(size_t n, size_t size)
{
    void *p = calloc(n, size);
    assert(p);
    return p;
}

void queue_init(size_t n)
{
    content = aalloc(n, sizeof * content);
    maxsize = n;
    headidx = 0;
    tailidx = 0;
    count   = 0;
}

int queue_empty()
{
    return count == 0;
}

static void push_back(Item n)
{
    int next;
    next             = (tailidx + 1) % maxsize;
    content[tailidx] = n;
    tailidx          = next;
    count++;
}

static void queue_push_del_old(Item n)
{
    delete(n);
    push_back(n);
}

static void queue_push_ignore_new(Item n)
{
    if (find(n) != -1) { /* element exist */
        return ;    /* just return */
    }

    push_back(n);
}

void queue_push(Item n)
{
#if defined (DEL_OLD)
    queue_push_del_old(n);
#elif defined (IGNORE_NEW)
    queue_push_ignore_new(n);
#endif
}

/**
 * @brief find whether the element is in the queue
 *
 * @param n the element to be search
 *
 * @return the index of the element, or -1 if not found
 */
static int find(Item n)
{
    size_t i;

    for (i = headidx; i != tailidx; i = (i + 1) % maxsize) {
        if (content[i] == n) { /* found */
            return i;
        }
    }

    return -1; /* not found */
}

static void delete(Item n)
{
    int idx;
    int next;
    size_t cur; /* current value to be replaced */

    if ((idx = find(n)) == -1) { /* element not found */
        return;
    }

    for (next = cur = idx; cur != tailidx - 1; cur = next) {
        next         = (next + 1) % maxsize;
        content[cur] = content[next];
    }

    tailidx = (tailidx - 1 + maxsize) % maxsize;
    count--;
}

Item queue_pop()
{
    Item reval;
    int idx;
    assert(!queue_empty());
    idx = rand() % count;
    reval   = content[idx];
    delete(reval);
    return reval;
}

void queue_finalize()
{
    while (!queue_empty()) {
        queue_pop();
    }

    free(content);
}
