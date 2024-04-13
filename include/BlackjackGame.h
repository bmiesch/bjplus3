#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;

class BlackjackGame {
private:
    Deck fullDeck;
    Dealer dealer;
    std::vector<Player> players;
    bool isPlus3;
    bool standardBets;
    json resultsBuffer;

    Card getCard();
    int askForBet(const std::string& prompt);
    void getBets();
    void dealInitialRound();
    void dealRound();
    void dealCardsToDealer();
    void finishRound();
    bool isStraight(Card card1, Card card2, Card card3); // In any order
    void plus3Check();

public:
    BlackjackGame(int numPlayers, int numDecks, bool isPlus3, bool standardBets);
    void play();
    void reset();
    void logGameResult(int gameID);
    void writeResultsToFile();
};

#endif // BLACKJACKGAME_H
