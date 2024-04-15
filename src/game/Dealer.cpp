#include "Dealer.h"

Dealer::Dealer() : hand(), handValue(0), busted(false) {}

void Dealer::addCard(Card card) {
    hand.push_back(card);
    handValue = calculateHandValue(hand);
}

int Dealer::getHandValue() const {
    return handValue;
}

Card Dealer::getUpCard() const {
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

bool Dealer::isBusted() const {
    return busted;
}

void Dealer::setBusted(bool val) {
    busted = val;
}

std::vector<Card> Dealer::getHand() const {
    return hand;
}
