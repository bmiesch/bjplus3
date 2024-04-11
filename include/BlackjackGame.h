#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include <vector>

class BlackjackGame {
private:
    Deck fullDeck;
    Dealer dealer;
    std::vector<Player> players;
    bool isPlus3;

    Card getCard();
    void getBets();
    void dealInitialRound();
    void dealRound();
    void dealCardsToDealer();
    void finishRound();
    bool isStraight(Card card1, Card card2, Card card3); // In any order
    void plus3Check();

public:
    BlackjackGame(int numPlayers, int numDecks, bool isPlus3);
    void play();
};

#endif // BLACKJACKGAME_H
