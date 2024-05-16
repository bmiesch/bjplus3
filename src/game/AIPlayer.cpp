#include "AIPlayer.h"
#include <algorithm>
#include <cctype>
#include <sstream>


std::string AIPlayer::formatGameState(int handIndex, Card dealerUpCard, bool canSplit) {
    std::vector<Card> cards = getHand(handIndex)->getCards();
    std::string handCards;
    for (const auto& card : cards) {
        handCards += card.toString() + " ";
    }

    std::string prompt = "Dealer up card is " + dealerUpCard.toString() +
    ". Your cards are " + handCards + ". You " + (canSplit ? "can split if you want to." : "cannot split.") +
    " Your goal is to maximize your odds of winning this game of blackjack. Respond with one action: hit, stand, double, or split. Only respond with the action with no additional text.";
    return prompt;
}

PlayerAction AIPlayer::parseDecision(const std::string& decision) {
    std::string lowerDecision = decision;
    std::transform(lowerDecision.begin(), lowerDecision.end(), lowerDecision.begin(), ::tolower);

    // Extract the first word from the decision
    std::istringstream iss(lowerDecision);
    std::string action;
    iss >> action;

    if (action == "hit") {
        return PlayerAction::HIT;
    } else if (action == "stand") {
        return PlayerAction::STAND;
    } else if (action == "double" || action == "double down") {
        return PlayerAction::DOUBLE_DOWN;
    } else if (action == "split") {
        return PlayerAction::SPLIT;
    } else {
        throw std::invalid_argument("Invalid decision: " + decision);
    }
}

