#include <assert.h>
#include <stdio.h>

#include "deque.h"

#define MAX 10
static Item content[MAX];
static size_t head  = 0;
static size_t tail  = 0;
static size_t count = 0;
static int deque_full();
void deque_push_front(Item n);

void deque_push_front(Item n)
{
    assert(!deque_full());

    if (deque_empty()) {
        head = 0;
        tail = 1;
    }

    content[head] = n;
    head          = (head - 1 + MAX) % MAX;
    count++;
}

static int deque_full()
{
    return count == MAX;
}

static void set_init_state()
{
    head = 0;
    tail = 1;
}

void deque_push_back(Item n)
{
    assert(!deque_full());

    if (deque_empty()) {
        set_init_state();
    }

    content[tail] = n;
    tail          = (tail + 1) % MAX;
    count++;
}

int deque_empty()
{
    return count == 0;
}

Item deque_pop_front()
{
    assert(!deque_empty());
    head = (head + 1) % MAX;
    count--;
    return content[head];
}

Item deque_pop_back()
{
    assert(!deque_empty());
    tail = (tail - 1 + MAX) % MAX;
    count--;
    return content[tail];
}

Item deque_front()
{
    assert(!deque_empty());
    size_t index = (head + 1) % MAX;
    return content[index];
}

Item deque_back()
{
    assert(!deque_empty());
    size_t index = (tail - 1 + MAX) % MAX;
    return content[index];
}
