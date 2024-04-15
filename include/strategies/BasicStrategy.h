#include "IPlayStrategy.h"
#include "utils.h"


class BasicStrategy : public IPlayStrategy {
public:
    BasicStrategy();
    PlayerAction decideAction(const std::vector<Card>& hand, Card dealerCard, bool canSplit) override;
private:
    bool shouldSplit(const std::vector<Card>& hand, Card dealerCard);
};

