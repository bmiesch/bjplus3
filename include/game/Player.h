#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Hand.h"
#include <vector>
#include "IBetStrategy.h"
#include "utils.h"
#include <memory>

class Player {
public:
    Player(int id, int initialBankroll, int numHands, IBetStrategy* betStrategy)
        : id(id), bankroll(initialBankroll), initialNumHands(numHands), betStrategy(betStrategy) {}

    virtual ~Player() {
        delete betStrategy;
    }

    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;

    virtual PlayerAction act(int handIndex, Card dealerUpCard, bool canSplit) = 0;

    void reset();
    int getId() const;
    void createHand(int bet);
    int getNumHands() const;
    Hand* getHand(int handIndex);
    void splitHand(int handIndex);
    int getBankroll() const;
    void updateBankroll(int val);
    int getInitialNumHands() const;
    int makeBet();
    int makeSideBet();

private:
    std::vector<Hand> hands;
    int id;
    int curBet;
    int curSideBet;
    int bankroll;
    int initialNumHands;
    IBetStrategy* betStrategy;
};

#endif // PLAYER_H
