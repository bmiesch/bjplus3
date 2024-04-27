#ifndef UTILS_H
#define UTILS_H

#include "Hand.h"
#include <vector>

enum class PlayerAction {
    HIT,
    STAND,
    DOUBLE_DOWN,
    SPLIT
};

int calculateHandValue(Hand* hand);
int calculateHandValue(std::vector<Card> hand);

bool isHandSoft(Hand* hand);

#endif // UTILS_H
