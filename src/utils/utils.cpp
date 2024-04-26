#include "utils.h"
#include "Card.h"

int calculateHandValue(Hand* hand) {
    int val = 0;
    int aceCount = 0;

    for (const Card& c : hand->getCards()) {
        val += c.getValue();
        if (c.getRank() == Card::ACE) {
            aceCount++;
        }
    }

    while (val > 21 && aceCount > 0) {
        val -= 10;
        aceCount--;
    }

    return val;
}


bool isHandSoft(Hand* hand) {
    int total = 0;
    bool hasAce = false;

    for (const Card& card : hand->getCards()) {
        int value = card.getValue();
        total += value;
        if (card.getRank() == Card::ACE) {
            hasAce = true;
        }
    }

    return hasAce && (total + 10 <= 21);
}

