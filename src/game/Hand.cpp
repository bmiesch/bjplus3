#include "Hand.h"
#include "utils.h"

Hand::Hand(int bet) : value(0), bet(bet), busted(false), sideBet(0), sideOutcome("") {}

void Hand::addCard(Card card) {
    cards.push_back(card);
    value = calculateHandValue(this);
}

void Hand::removeCardAt(int index) {
    cards.erase(cards.begin() + index);
    value = calculateHandValue(this);
}

int Hand::getValue() const {
    return value;
}

bool Hand::isBusted() const {
    return busted;
}

void Hand::setBusted(bool busted) {
    this->busted = busted;
}

std::vector<Card> Hand::getCards() const {
    return cards;
}

int Hand::getBet() const {
    return bet;
}

void Hand::setBet(int bet) {
    this->bet = bet;
}

int Hand::getSideBet() const {
    return sideBet;
}

void Hand::setSideBet(int sideBet) {
    this->sideBet = sideBet;
}

std::string Hand::getSideOutcome() const {
    return sideOutcome;
}

void Hand::setSideOutcome(std::string sideOutcome) {
    this->sideOutcome = sideOutcome;
}

void Hand::clear() {
    cards.clear();
    value = 0;
    busted = false;
}

void Hand::setOutcome(std::string outcome) {
    this->outcome = outcome;
}

std::string Hand::getOutcome() const {
    return outcome;
}

