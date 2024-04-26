#ifndef PLAY_STRATEGY_H
#define PLAY_STRATEGY_H

#include <vector>
#include "Card.h"
#include "Hand.h"
#include "utils.h"

class IPlayStrategy {
public:
    virtual PlayerAction decideAction(Hand* hand, Card dealerCard, bool canSplit) = 0;
    virtual ~IPlayStrategy() {}
};

#endif // PLAY_STRATEGY_H

