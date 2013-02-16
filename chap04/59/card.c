#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "card.h"

#define T card_t

typedef enum suit suit_t;

enum suit {
    SPADE = 0,
    HEART,
    CLUB,
    DIAMOND,
};

struct T {
    int number;
    int suit;
};

static void *alloc(size_t size);

T card_init(int n, int s)
{
    T t       = alloc(sizeof * t);
    t->number = n;
    t->suit   = s;
    return t;
}

static void *alloc(size_t size)
{
    T t = malloc(size);
    assert(t);
    return t;
}

void card_finalize(T t)
{
    free(t);
}

void card_print(T t)
{
    printf("%3d %d\n", t->number, t->suit);
}
