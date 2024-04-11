#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

class Player {
public:
    Player();

    void addCard(Card card);

    void reset();

    std::vector<Card> getHand();

    int getHandValue();

    bool isBusted();

    void setBusted(bool val);

    int getChips();

    void addChips(int val);

    void removeChips(int val);

    void setCurBet(int val);

    int getCurBet();

    void setCurSideBet(int val);

    int getCurSideBet();

private:
    std::vector<Card> hand;
    int handValue;
    bool busted;

    int curBet;
    int curSideBet;
    int chips;
};

#endif // PLAYER_H
