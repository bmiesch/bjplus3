#include "Player.h"


void Player::reset() {
    for (Hand& hand : hands) {
        hand.clear();
    }
    hands.clear();
}

int Player::getId() const {
    return id;
}

void Player::createHand(int bet) {
    hands.push_back(Hand(bet));
}

int Player::getNumHands() const {
    return hands.size();
}

Hand* Player::getHand(int handIndex) {
    return &hands[handIndex];
}

void Player::splitHand(int handIndex) {
    Hand newHand(hands[handIndex].getBet());
    newHand.addCard(hands[handIndex].getCards()[1]);
    hands[handIndex].removeCardAt(1);

    hands.insert(hands.begin() + handIndex, newHand);
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

