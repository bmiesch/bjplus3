#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

class Player {
public:
    Player();

    void addCard(Card card);

    void reset();

    std::vector<Card> getHand() const;

    int getHandValue() const;

    bool isBusted() const;

    void setBusted(bool val);

    int getChips() const;

    void addChips(int val);

    void removeChips(int val);

    void setCurBet(int val);

    int getCurBet() const;

    void setCurSideBet(int val);

    int getCurSideBet() const;

    std::string getOutcome() const;

    void setOutcome(std::string val);

    std::string getSideOutcome() const;

    void setSideOutcome(std::string val);

private:
    std::vector<Card> hand;
    int handValue;
    bool busted;

    int curBet;
    int curSideBet;
    int chips;
    
    std::string outcome;
    std::string sideOutcome;
};

#endif // PLAYER_H
