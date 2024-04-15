#include "BasicStrategy.h"
#include "utils.h"

BasicStrategy::BasicStrategy() : IPlayStrategy() {}

PlayerAction BasicStrategy::decideAction(const std::vector<Card>& hand, Card dealerCard, bool canSplit) {
    int handValue = calculateHandValue(hand);
    bool isSoft = isHandSoft(hand);
    int dealerUpCardValue = dealerCard.getValue();


    // Check for splitting
    if (canSplit && shouldSplit(hand, dealerCard)) {
        return PlayerAction::SPLIT;
    }

    // Check for Double Down
    if (hand.size() == 2 && (handValue == 9 && dealerUpCardValue >= 3 && dealerUpCardValue <= 6) ||
        (handValue == 10 && dealerUpCardValue <= 9) ||
        (handValue == 11)) {
        return PlayerAction::DOUBLE_DOWN;
    }

    // Decisions for soft hands
    if (isSoft) {
        if (handValue <= 17) {
            return PlayerAction::HIT;
        } else if (handValue == 18) {
            if (dealerUpCardValue >= 9 || dealerUpCardValue == 11) {
                return PlayerAction::HIT;
            } else if (dealerUpCardValue >= 3 && dealerUpCardValue <= 6) {
                return PlayerAction::DOUBLE_DOWN;
            } else {
                return PlayerAction::STAND;
            }
        } else {  // Soft 19 or higher
            return PlayerAction::STAND;
        }
    }

    // Decisions for hard hands
    if (handValue <= 11) {
        return PlayerAction::HIT;
    } else if (handValue == 12) {
        if (dealerUpCardValue < 4 || dealerUpCardValue > 6) {
            return PlayerAction::HIT;
        } else {
            return PlayerAction::STAND;  // Dealer shows 4, 5, or 6
        }
    } else if (handValue >= 13 && handValue <= 16) {
        if (dealerUpCardValue >= 7) {
            return PlayerAction::HIT;  // Dealer shows 7 or higher
        } else {
            return PlayerAction::STAND;  // Dealer shows 6 or lower
        }
    } else if (handValue >= 17) {
        return PlayerAction::STAND;
    }

    return PlayerAction::STAND;
}

bool BasicStrategy::shouldSplit(const std::vector<Card>& hand, Card dealerCard) {
    if (hand.size() != 2 || hand[0].getRank() != hand[1].getRank()) {
        return false;
    }

    int rank = hand[0].getRank();
    int dealerValue = dealerCard.getValue();

    switch (rank) {
        case 14:
        case 8:
            return true;
        case 2:
        case 3: 
        case 7:
            return dealerValue < 8;  // Split 2s, 3s, 7s against dealer 2-7
        case 4:
            return dealerValue == 5 || dealerValue == 6;  // Split 4s only against dealer 5 or 6
        case 6:
            return dealerValue < 7;  // Split 6s against dealer 2-6
        case 9:
            return dealerValue != 7 && dealerValue != 10 && dealerValue != 11;  // Split 9s against dealer 2-6, 8, 9
        default:
            return false;  // Do not split 5s, 10s
    }
}
