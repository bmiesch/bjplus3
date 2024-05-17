#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "Card.h"
#include "Deck.h"
#include "AIPlayer.h"
#include "OllamaClient.h"
#include "StandardPlayer.h"
#include "Dealer.h"
#include "GameLogger.h"
#include "ConsBetStrategy.h"
#include "AggrBetStrategy.h"
#include "BasicStrategy.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;


class GameConfig {
public:
    std::vector<Player*> players;
    int numDecks;
    bool isPlus3;

    GameConfig(const std::vector<Player*>& players, int numDecks, bool isPlus3)
        : players(players), numDecks(numDecks), isPlus3(isPlus3) {}
};


class BlackjackGame {
private:
    Deck fullDeck;
    Dealer dealer;
    GameConfig config;
    GameLogger logger;

    void dealInitialRound();
    void dealRound();
    void dealCardsToDealer();
    void finishRound();
    bool isStraight(Card card1, Card card2, Card card3);
    // As of now only one side bet is supported
    void finishSideBet();
    
public:
    BlackjackGame(const GameConfig& config);
    void play();
    void reset();
    void logGameResult(int gameID);
    void writeResultsToFile();
};

#endif // BLACKJACKGAME_H
