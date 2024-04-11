#include "Dealer.h"

Dealer::Dealer() : hand(), handValue(0), busted(false) {}

void Dealer::addCard(Card card) {
    hand.push_back(card);
    if (card.getRank() == Card::ACE) {
        handValue += 11;
    }
    else {
        handValue += card.getRank();
    }
}

int Dealer::getHandValue() {
    return handValue;
}

Card Dealer::getUpCard() {
    if (hand.size() > 0) {
        return hand[0];
    }
    else {
        throw std::out_of_range("Dealer has no cards");
    }
}

void Dealer::reset() {
    hand.clear();
    handValue = 0;
    busted = false;
}

bool Dealer::isBusted() {
    return busted;
}

void Dealer::setBusted(bool val) {
    busted = val;
}
