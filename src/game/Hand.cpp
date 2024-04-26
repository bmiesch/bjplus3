#include "Hand.h"
#include "utils.h"

Hand::Hand(int bet) : bet(bet), busted(false) {}

void Hand::addCard(Card card) {
    cards.push_back(card);
    value = calculateHandValue(this);
}

int Hand::getValue() const {
    return value;
}

bool Hand::isBusted() const {
    return busted;
}

void Hand::setBusted(bool val) {
    busted = val;
}

int Hand::getBet() const {
    return bet;
}

std::vector<Card> Hand::getCards() const {
    return cards;
}

void Hand::setBet(int bet) {
    bet = bet;
}

