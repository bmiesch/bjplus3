#include "IPlayStrategy.h"
#include "utils.h"


class BasicStrategy : public IPlayStrategy {
public:
    BasicStrategy();
    PlayerAction decideAction(Hand* hand, Card dealerCard, bool canSplit) override;
private:
    bool shouldSplit(Hand* hand, Card dealerCard);
};

