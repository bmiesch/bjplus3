#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Hand.h"
#include <vector>
#include "IBetStrategy.h"
#include "IPlayStrategy.h"
#include "utils.h"

class Player {
public:
    Player(int initialBankroll, IBetStrategy* betStrategy, IPlayStrategy* playStrategy);

    void reset();

    // Should addCard handle multiple hands?
    // void addCard(Card card);

    void createHand(int bet);
    int getNumHands() const;
    Hand* getHand(int handIndex);
    void splitHand(int handIndex);

    int getBankroll() const;
    void updateBankroll(int val);

    int makeBet();
    void setCurBet(int val);
    int getCurBet() const;
    int makeSideBet();
    int getCurSideBet() const;

    std::string getOutcome() const;
    void setOutcome(std::string val);

    std::string getSideOutcome() const;
    void setSideOutcome(std::string val);

    PlayerAction act(int handIndex, Card dealerUpCard, bool canSplit);

private:
    std::vector<Hand> hands;

    int curBet;
    int curSideBet;
    int bankroll;
    
    std::string outcome;
    std::string sideOutcome;

    IBetStrategy* betStrategy;
    IPlayStrategy* playStrategy;
};

#endif // PLAYER_H
