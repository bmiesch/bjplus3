#include "Deck.h"

Deck::Deck(int numDecks) {
    for(int i = 0; i < numDecks; i++) {
        for(int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
            for(int rank = Card::TWO; rank <= Card::ACE; rank++) {
                cards.push_back(Card(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank)));
            }
        }
    }
}

Card Deck::drawCard() {
    if (!cards.empty()) {
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    } else {
        throw std::out_of_range("No more cards in the deck.");
    }
}

int Deck::getNumCardsLeft() {
    return cards.size();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}
