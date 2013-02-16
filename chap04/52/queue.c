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
static int find(Item n);

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

void queue_push(Item n)
{
    int found;
    size_t next;

    if ((found = find(n)) != -1) { /* element exist */
        /* move the elements after the found one */
        size_t i;   /* the place to be replaced */

        for (i = found; i != tailidx - 1; i = next) {
            next       = (i + 1) % maxsize;
            content[i] = content[next];
        }

        content[tailidx - 1] = n;
    } else { /* not found */
        next             = (tailidx + 1) % maxsize;
        content[tailidx] = n;
        tailidx          = next;
        count++;
    }
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

Item queue_pop()
{
    int reval;
    assert(!queue_empty());
    reval   = content[headidx];
    headidx = (headidx + 1) % maxsize;
    count--;
    return reval;
}

void queue_finalize()
{
    while (!queue_empty()) {
        queue_pop();
    }

    free(content);
}
