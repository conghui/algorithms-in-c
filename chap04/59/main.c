#include "deck.h"

int main(void)
{
    deck_t deck;
    deck = deck_init();
    deck_print(deck);
    deck_finalize(deck);
    return 0;
}
