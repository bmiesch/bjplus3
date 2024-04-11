#include "Player.h"

Player::Player() : hand(), handValue(0), busted(false), curBet(0), chips(100) {}

void Player::addCard(Card card) {
    hand.push_back(card);

    if (card.getRank() == Card::ACE) {
        if (handValue + 11 > 21) {
            handValue += 1;
        }
        else {
            handValue += 11;
        }
    }
    else {
        handValue += card.getRank();
    }
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

