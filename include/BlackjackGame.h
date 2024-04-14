#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "GameLogger.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;


class GameConfig {
public:
    int numPlayers;
    int numDecks;
    bool isPlus3;
    bool standardBets;

    GameConfig(int numPlayers, int numDecks, bool isPlus3, bool standardBets)
        : numPlayers(numPlayers), numDecks(numDecks), isPlus3(isPlus3), standardBets(standardBets) {}
};


class BlackjackGame {
private:
    Deck fullDeck;
    Dealer dealer;
    std::vector<Player> players;
    GameConfig config;
    GameLogger logger;

    Card getCard();
    int askForBet(const std::string& prompt);
    void getBets();
    void dealInitialRound();
    void dealRound();
    void dealCardsToDealer();
    void finishRound();
    bool isStraight(Card card1, Card card2, Card card3);
    void plus3Check();
    
public:
    BlackjackGame(const GameConfig& config);
    void play();
    void reset();
    void logGameResult(int gameID);
    void writeResultsToFile();
};

#endif // BLACKJACKGAME_H
