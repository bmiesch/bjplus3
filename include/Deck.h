#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck {
    public:
        Deck(int size);

        Card drawCard();

        int getNumCardsLeft();

        void shuffle();

    private:
        std::vector<Card> cards;
        // int curNumCards;
};

#endif // DECK_H
