#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "queue.h"

#define SIZE 10

static Item content[SIZE];
static size_t count = 0;
static size_t head  = 0;
static size_t tail  = 0;


static void queue_error(const char *fmt, ...);

void queue_push(Item n)
{
    if (queue_full()) {
        queue_error("the queue is full");
    }

    content[tail++] = n;
    tail %= SIZE;
    count++;
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

int queue_full()
{
    return count == SIZE;
}

Item queue_pop()
{
    if (queue_empty()) {
        queue_error("the queue is empty");
    }

    Item tmp = content[head++];
    head    %= SIZE;
    count--;
    return tmp;
}

int queue_empty()
{
    return count == 0;
}
