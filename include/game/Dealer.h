#ifndef DEALER_H
#define DEALER_H

#include <vector>
#include "Card.h"
#include "utils.h"

class Dealer {
public:
    Dealer();

    void addCard(Card card);
    
    Card getUpCard() const;

    int getHandValue() const;

    void reset();

    bool isBusted() const;

    void setBusted(bool val);

    std::vector<Card> getHand() const;

private:
    std::vector<Card> hand;
    int handValue;
    bool busted;
};

#endif // DEALER_H

