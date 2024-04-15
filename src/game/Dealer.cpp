#include "Dealer.h"

Dealer::Dealer() : hand(), handValue(0), busted(false) {}

void Dealer::addCard(Card card) {
    std::cout << "Dealer Added Card: " << card << std::endl;
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
