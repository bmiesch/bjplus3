#ifndef AGGR_BET_STRATEGY_H
#define AGGR_BET_STRATEGY_H

#include "IBetStrategy.h"

class AggrBetStrategy : public IBetStrategy {
public:
    AggrBetStrategy() : IBetStrategy() {}
    int bet(int curBankroll) override {
        return static_cast<int>(0.10 * curBankroll);
    }
    int sideBet(int curBankroll) override {
        return static_cast<int>(0.02 * curBankroll);
    }
};


#endif // AGGR_BET_STRATEGY_H

