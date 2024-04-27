#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Hand.h"
#include <vector>
#include "IBetStrategy.h"
#include "IPlayStrategy.h"
#include "utils.h"
#include <memory>

class Player {
public:
    Player(int id, int initialBankroll, IBetStrategy* betStrategy, IPlayStrategy* playStrategy);
    ~Player();

    // Copy constructor and copy assignment operator should be handled properly if you allow copying of Player objects.
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    void reset();

    int getId() const;

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

    PlayerAction act(int handIndex, Card dealerUpCard, bool canSplit);

private:
    std::vector<Hand> hands;

    int id;
    int curBet;
    int curSideBet;
    int bankroll;

    IBetStrategy* betStrategy;
    IPlayStrategy* playStrategy;
};

#endif // PLAYER_H
