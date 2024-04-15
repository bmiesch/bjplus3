#ifndef CONS_BET_STRATEGY_H
#define CONS_BET_STRATEGY_H

#include "IBetStrategy.h"

class ConsBetStrategy : public IBetStrategy {
public:
    ConsBetStrategy() : IBetStrategy() {}
    int bet(int curBankroll) override {
        return static_cast<int>(0.02 * curBankroll);
    }
    int sideBet(int curBankroll) override {
        return static_cast<int>(0.01 * curBankroll);
    }
};

#endif // CONS_BET_STRATEGY_H
