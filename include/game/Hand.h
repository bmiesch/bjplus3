#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

class Hand {
public:
    Hand(int bet);

    void addCard(Card card);
    int getValue() const;
    bool isBusted() const;
    void setBusted(bool val);
    int getBet() const;
    void setBet(int bet);

    std::vector<Card> getCards() const;
    void clear();

private:
    std::vector<Card> cards;
    int value;
    int bet;
    bool busted;
};

#endif

