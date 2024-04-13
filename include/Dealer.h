#ifndef DEALER_H
#define DEALER_H

#include <vector>
#include "Card.h"

class Dealer {
public:
    Dealer();

    void addCard(Card card);
    
    Card getUpCard();

    int getHandValue();

    void reset();

    bool isBusted();

    void setBusted(bool val);

    std::vector<Card> getHand();

private:
    std::vector<Card> hand;
    int handValue;
    bool busted;
};

#endif // DEALER_H

