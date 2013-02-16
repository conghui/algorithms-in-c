#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "deque.h"

#define T link

static T head = NULL;
static T tail = NULL;
static void *alloc(size_t size);
static T newnode(Item entry, T prev, T next);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static T newnode(Item entry, T prev, T next)
{
    T nn      = alloc(sizeof * nn);
    nn->prev  = prev;
    nn->next  = next;
    nn->entry = entry;
    return nn;
}

void deque_push_front(Item n)
{
    if (head == NULL) { /* the deque is empty */
        head = tail = newnode(n, NULL, NULL);
        return;
    }

    /* the deque is not empty */
    T nn       = newnode(n, NULL, head);
    head->prev = nn;
    head       = nn;
}

void deque_push_back(Item n)
{
    if (head == NULL) { /* the deque is empty */
        head = tail = newnode(n, NULL, NULL);
        return;
    }

    /* the deque is not empty */
    T nn       = newnode(n, tail, NULL);
    tail->next = nn;
    tail       = nn;
}

Item deque_pop_front()
{
    assert(!deque_empty());

    if (head == tail) { /* the last element */
        tail = NULL;
    }

    T tmp = head;
    Item ret = head->entry;
    head  = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    free(tmp);
    return ret;
}


Item deque_pop_back()
{
    assert(!deque_empty());

    if (head == tail) { /* the last element */
        head = NULL;
    }

    T tmp    = tail;
    Item ret = tail->entry;
    tail     = tail->prev;

    if (tail != NULL) {
        tail->next = NULL;
    }

    free(tmp);
    return ret;
}

int deque_empty()
{
    return head == NULL && tail == NULL;
}

Item deque_front()
{
    assert(!deque_empty());
    return head->entry;
}

Item deque_back()
{
    assert(!deque_empty());
    return tail->entry;
}

void deque_dump()
{
    T cur;

    if (deque_empty()) {
        putchar('\n');
        return ;
    }

    printf("\t\t\t");

    for (cur = head; cur != tail; cur = cur->next) {
        printf("%c ", cur->entry);
    }

    /* print the last entry */
    printf("%c\n", tail->entry);
}
