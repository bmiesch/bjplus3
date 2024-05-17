#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include "LLMClient.h"

class AIPlayer : public Player {
public:
    AIPlayer(int id, int initialBankroll, int initialNumHands, IBetStrategy* betStrategy, LLMClient* client)
        : Player(id, initialBankroll, initialNumHands, betStrategy), client(client) {}
    
    ~AIPlayer() override {
        delete client;
    }
    
    AIPlayer(const AIPlayer& other) = delete;
    AIPlayer& operator=(const AIPlayer& other) = delete;

    PlayerAction act(int handIndex, Card dealerUpCard, bool canSplit) override {
        std::string gameState = formatGameState(handIndex, dealerUpCard, canSplit);
        std::string decision = client->getDecision(gameState);
        return parseDecision(decision);
    }

private:
    LLMClient* client;

    std::string formatGameState(int handIndex, Card dealerUpCard, bool canSplit);
    PlayerAction parseDecision(const std::string& decision);
};

#endif // AIPLAYER_H
