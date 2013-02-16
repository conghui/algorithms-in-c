#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "queue.h"

#define T node_t

static T head = NULL;
static T tail = NULL;
static void queue_error(const char *fmt, ...);
static void *alloc(size_t size);

T newnode(Item n, T next)
{
    T nn      = alloc(sizeof * nn);
    nn->entry = n;
    nn->next  = next;
    return nn;
}

void queue_push(Item n)
{
    T nn = newnode(n, NULL);

    if (head == NULL) { /* the queue is empty */
        head = tail = nn;
        return ;
    }

    tail->next = nn;
    tail = nn;
}

Item queue_pop()
{
    if (queue_empty()) {
        queue_error("the queue is empty");
    }

    Item result = head->entry;
    T    tmp    = head;
    head        = head->next;
    free(tmp);
    return result;
}

int queue_empty()
{
    return head == NULL;
}

static void queue_error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
    va_end(ap);
}
static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}
