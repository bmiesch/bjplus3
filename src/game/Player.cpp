#include "Player.h"

Player::Player(int initialBankroll, IBetStrategy* betStrategy)
    : hand(), handValue(0), busted(false), curBet(0), bankroll(initialBankroll), betStrategy(betStrategy) {}

void Player::addCard(Card card) {
    std::cout << "Player Added Card: " << card << std::endl;
    hand.push_back(card);

    // Recalculate hand value from scratch
    handValue = 0;
    int aceCount = 0;

    for (const Card& c : hand) {
        handValue += c.getValue();
        if (c.getRank() == Card::ACE) {
            aceCount++;
        }
    }

    while (handValue > 21 && aceCount > 0) {
        handValue -= 10;
        aceCount--;
    }

    std::cout << "New value: " << handValue << std::endl;
}

void Player::reset() {
    hand.clear();
    handValue = 0;
    busted = false;
}

std::vector<Card> Player::getHand() const {
    return hand;
}

int Player::getHandValue() const {
    return handValue;
}

bool Player::isBusted() const {
    return busted;
}

void Player::setBusted(bool val) {
    busted = val;
}

int Player::getBankroll() const {
    return bankroll;
}

void Player::updateBankroll(int val) {
    bankroll += val;
}

int Player::makeBet() {
    curBet = betStrategy->bet(bankroll);
    return curBet;
}
int Player::getCurBet() const {
    return curBet;
}

int Player::makeSideBet() {
    curSideBet = betStrategy->sideBet(bankroll);
    return curSideBet;
}
int Player::getCurSideBet() const {
    return curSideBet;
}

std::string Player::getOutcome() const {
    return outcome;
}

void Player::setOutcome(std::string str) {
    outcome = str;
}

std::string Player::getSideOutcome() const {
    return sideOutcome;
}

void Player::setSideOutcome(std::string str) {
    sideOutcome = str;
}

