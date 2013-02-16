#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "card.h"
#include "deck.h"

#define T deck_t

#define DECKSIZE 52
#define N        13 /* # of value */
#define M        4 /* # of suit */

struct T {
    card_t card[DECKSIZE];
};
static void *alloc(size_t size);

static void *alloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

T deck_init()
{
    T t = alloc(sizeof * t);
    int i;
    int j;
    int count = 0;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            t->card[count++] = card_init(i, j);
        }
    }

    return t;
}

void deck_finalize(T t)
{
    if (t == NULL) {
        return ;
    }

    int i;

    for (i = 0; i < DECKSIZE; i++) {
        card_finalize(t->card[i]);
    }

    free(t);
}

void deck_print(T t)
{
    int i;

    for (i = 0; i < DECKSIZE; i++) {
        card_print(t->card[i]);
    }
}
