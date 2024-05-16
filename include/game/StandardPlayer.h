#ifndef STANDARD_PLAYER_H
#define STANDARD_PLAYER_H

#include "Player.h"
#include "IPlayStrategy.h"

class StandardPlayer : public Player {
public:
    StandardPlayer(int id, int initialBankroll, IBetStrategy* betStrategy, IPlayStrategy* playStrategy)
        : Player(id, initialBankroll, betStrategy), playStrategy(playStrategy) {}

    ~StandardPlayer() override {
        delete playStrategy;
    }

    PlayerAction act(int handIndex, Card dealerUpCard, bool canSplit) override {
        return playStrategy->decideAction(getHand(handIndex), dealerUpCard, canSplit);
    }

private:
    IPlayStrategy* playStrategy;
};

#endif // STANDARD_PLAYER_H
