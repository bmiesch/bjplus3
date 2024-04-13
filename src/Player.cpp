#include "Player.h"

Player::Player() : hand(), handValue(0), busted(false), curBet(0), chips(100) {}

void Player::addCard(Card card) {
    std::cout << "Player Added Card: " << card << std::endl;
    hand.push_back(card);
    handValue += card.getValue();

    int aceCount = 0;
    // First pass: add all card values, count aces
    for (Card& card : hand) {
        if (card.getRank() == Card::ACE) {
            aceCount++;
        }
    }

    // Second pass: adjust for aces if total value exceeds 21
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

std::vector<Card> Player::getHand() {
    return hand;
}

int Player::getHandValue() {
    return handValue;
}

bool Player::isBusted() {
    return busted;
}

void Player::setBusted(bool val) {
    busted = val;
}

int Player::getChips() {
    return chips;
}

void Player::addChips(int val) {
    chips += val;
}

void Player::removeChips(int val) {
    chips -= val;
}

void Player::setCurBet(int val) {
    curBet = val;
}

int Player::getCurBet() {
    return curBet;
}

void Player::setCurSideBet(int val) {
    curSideBet = val;
}

int Player::getCurSideBet() {
    return curSideBet;
}

std::string Player::getOutcome() {
    return outcome;
}

void Player::setOutcome(std::string str) {
    outcome = str;
}

std::string Player::getSideOutcome() {
    return sideOutcome;
}

void Player::setSideOutcome(std::string str) {
    sideOutcome = str;
}

