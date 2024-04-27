#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

class Hand {
public:
    Hand(int bet);

    void addCard(Card card);
    void removeCardAt(int index);
    int getValue() const;
    bool isBusted() const;
    void setBusted(bool busted);

    int getBet() const;
    void setBet(int bet);
    std::string getOutcome() const;
    void setOutcome(std::string outcome);

    int getSideBet() const;
    void setSideBet(int sideBet);
    std::string getSideOutcome() const;
    void setSideOutcome(std::string sideOutcome);

    std::vector<Card> getCards() const;
    void clear();

private:
    std::vector<Card> cards;
    int value;
    int bet;
    std::string outcome;
    int sideBet;
    std::string sideOutcome;
    bool busted;
};

#endif

