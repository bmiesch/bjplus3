#include "Player.h"

Player::Player(int initialBankroll, IBetStrategy* betStrategy, IPlayStrategy* playStrategy)
    : hand(), handValue(0), busted(false), curBet(0), bankroll(initialBankroll), betStrategy(betStrategy), playStrategy(playStrategy) {}

void Player::addCard(Card card) {
    hand.push_back(card);
    handValue = calculateHandValue(hand);
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
void Player::setCurBet(int val) {
    curBet = val;
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

PlayerAction Player::act(Card dealerUpCard, bool canSplit) {
    return playStrategy->decideAction(hand, dealerUpCard, canSplit);
}

