#ifndef BET_STRATEGY_H
#define BET_STRATEGY_H

class IBetStrategy {
public:
    virtual int bet(int curBankroll) = 0;
    virtual int sideBet(int curBankroll) = 0;
    virtual ~IBetStrategy() {}
};

#endif // BET_STRATEGY_H

