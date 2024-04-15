#ifndef PLAY_STRATEGY_H
#define PLAY_STRATEGY_H

#include <vector>
#include "Card.h"

class IPlayStrategy {
public:
    virtual bool hit(std::vector<Card> hand, Card dealerCard) = 0;
    virtual bool doubleDown(std::vector<Card> hand, Card dealerCard) = 0;
    virtual bool split(std::vector<Card> hand, Card dealerCard) = 0;
    virtual ~IPlayStrategy() {}
};

#endif // PLAY_STRATEGY_H

