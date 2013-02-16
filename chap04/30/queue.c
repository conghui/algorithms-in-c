#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define SIZE 10

typedef struct T {
    Item content[SIZE];
    size_t front;
    size_t rear;
    size_t count;
} queue_t;

static queue_t queue;

void queue_init()
{
    queue.count = 0;
    queue.front = SIZE;
    queue.rear  = 0;
}

void queue_push(Item n)
{
    if (queue_full()) {
        fprintf(stderr, "the queue is full\n");
        exit(EXIT_FAILURE);
    }

    queue.content[queue.rear++] = n;
    queue.rear %= SIZE;
    queue.count++;
}

Item queue_pop()
{
    if (queue_empty()) {
        fprintf(stderr, "the queue is empty\n");
        exit(EXIT_FAILURE);
    }

    queue.front %= SIZE;
    queue.count--;
    return queue.content[queue.front++];
}

int queue_empty()
{
    return queue.count == 0;
}

int queue_full()
{
    return queue.count == SIZE;
}
