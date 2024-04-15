#ifndef UTILS_H
#define UTILS_H

#include "Card.h"
#include <vector>

enum class PlayerAction {
    HIT,
    STAND,
    DOUBLE_DOWN,
    SPLIT
};

int calculateHandValue(const std::vector<Card>& hand);

bool isHandSoft(const std::vector<Card>& hand);

#endif // UTILS_H
