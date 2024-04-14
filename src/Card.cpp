#include "Card.h"

Card::Card(Suit s, Rank r) : suit(s), rank(r) {
    switch(rank) {
        case ACE:
            value = 11;
            break;
        case KING:
        case QUEEN:
        case JACK:
            value = 10;
            break;
        default:
            value = static_cast<int>(rank);
    }
}

Card::Suit Card::getSuit() const {
    return suit;
}

Card::Rank Card::getRank() const {
    return rank;
}

int Card::getValue() const {
    return value;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    const char* suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* rankNames[] = { "", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    os << rankNames[card.rank] << " of " << suitNames[card.suit];
    return os;
}

std::string Card::toString() const {
    const std::string suitNames[] = { "H", "D", "C", "S" };
    const std::string rankNames[] = { "", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    return rankNames[static_cast<int>(rank)] + suitNames[static_cast<int>(suit)];
}