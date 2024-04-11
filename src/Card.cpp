#include "Card.h"

Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

Card::Suit Card::getSuit() {
    return suit;
}

Card::Rank Card::getRank() {
    return rank;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    const char* suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* rankNames[] = { "", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    os << rankNames[card.rank] << " of " << suitNames[card.suit];
    return os;
}
