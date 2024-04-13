#include "Dealer.h"

Dealer::Dealer() : hand(), handValue(0), busted(false) {}

void Dealer::addCard(Card card) {
    std::cout << "Dealer Added Card: " << card << std::endl;
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

std::vector<Card> Dealer::getHand() {
    return hand;
}
