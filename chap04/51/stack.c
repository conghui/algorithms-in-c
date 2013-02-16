#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

typedef struct T *T;

struct T {
    Item entry;
    T    next;
    T    prev;
};

static T       head;        /* the head of the stack            */
static size_t  max_size;   /* maximum number of element       */
static T      *exist;      /* points to the existing elements */
static void *alloc(size_t size);
static T newnode(Item n, T prev, T next);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static T newnode(Item n, T prev, T next)
{
    T nn      = alloc(sizeof * nn);
    nn->entry = n;
    nn->prev  = prev;
    nn->next  = next;
    return nn;
}

void stack_init(size_t size)
{
    size_t i;
    max_size = size;
    head      = NULL;
    exist    = alloc(size * sizeof * exist);

    for (i = 0; i < size; i++) {
        exist[i] = NULL;
    }
}

/* forget(delete) the old entry if exist */
void stack_push(Item n)
{
    if (exist[n] != NULL) { /* the element is exist */
        /* remote the element */
        if (exist[n] == head) { /* the exist one is the head */
            head = head->next;

            if (head != NULL) {
                head->prev = NULL;
            }
        } else {
            exist[n]->prev->next = exist[n]->next;

            if (exist[n]->next != NULL) {
                exist[n]->next->prev = exist[n]->prev;
            }
        }

        free(exist[n]);
        exist[n] = NULL;    /* un-register it */
    }

    T nn      = newnode(n, NULL, head);

    if (head != NULL) {
        head->prev = nn;
    }

    head       = nn;
    exist[n]  = nn; /* register it */
}

Item stack_pop()
{
    T tmp;
    Item reval;
    assert(!stack_empty());
    tmp   = head;
    reval = head->entry;
    head  = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    exist[reval] = NULL;    /* un-register it */
    free(tmp);
    return reval;
}

int stack_empty()
{
    return head == NULL;
}

void stack_final()
{
    while (!stack_empty()) {
        stack_pop();
    }

    free(exist);
}
