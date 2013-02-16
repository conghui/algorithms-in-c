#include <stdlib.h>
#include <assert.h>

#include "randlist.h"

typedef struct T *T;
struct T {
    Item entry;
    T    next;
};

static T head = NULL;
static T tail = NULL;
static size_t count = 0;

static void *alloc(size_t size);
static T newnode(Item n, T next);
static size_t rand_int(size_t n);
int randlist_empty();
void randlist_push(Item n);
Item randlist_pop();

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static T newnode(Item n, T next)
{
    T nn      = alloc(sizeof * nn);
    nn->next  = next;
    nn->entry = n;
    return nn;
}

int randlist_empty()
{
    return head == NULL && tail == NULL;
}

void randlist_push(Item n)
{
    if (head == NULL) { /* the list is empty */
        head = tail = newnode(n, NULL);
    } else {
        tail->next = newnode(n, tail->next);
        tail       = tail->next;
    }

    count++;
}

Item randlist_pop()
{
    assert(!randlist_empty());
    int index;
    Item rtval; /* return value */
    T   cur;
    T   prev;
    T   tmp;
    index = rand_int(count);

    if (index == 0) {
        tmp = head;
        rtval = head->entry;
        head = head->next;

        if (count == 1) { /* the last element */
            tail = NULL;
        }

        free(tmp);
        count--;
        return rtval;
    }

    cur = head;
    prev = NULL;

    while (index-- > 0 && cur->next != NULL) {
        prev = cur;
        cur = cur->next;
    }

    rtval = cur->entry;
    tmp        = cur;
    prev->next = cur->next;
    free(tmp);
    count--;
    return rtval;
}

static size_t rand_int(size_t n)
{
    return rand() % n;
}
