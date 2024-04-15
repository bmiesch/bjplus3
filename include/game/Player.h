#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include "IBetStrategy.h"
#include "IPlayStrategy.h"
#include "utils.h"

class Player {
public:
    Player(int initialBankroll, IBetStrategy* betStrategy, IPlayStrategy* playStrategy);

    void reset();

    void addCard(Card card);

    std::vector<Card> getHand() const;
    int getHandValue() const;

    bool isBusted() const;
    void setBusted(bool val);

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

    PlayerAction act(Card dealerUpCard, bool canSplit);

private:
    std::vector<Card> hand;
    int handValue;
    bool busted;

    int curBet;
    int curSideBet;
    int bankroll;
    
    std::string outcome;
    std::string sideOutcome;

    IBetStrategy* betStrategy;
    IPlayStrategy* playStrategy;
};

#endif // PLAYER_H
