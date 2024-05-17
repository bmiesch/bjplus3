#include "BlackjackGame.h"
#include <memory>

int main() {
    std::vector<Player*> players;
    players.push_back(new StandardPlayer(1, 100, 1, new ConsBetStrategy(), new BasicStrategy()));
    players.push_back(new AIPlayer(2, 100, 1, new ConsBetStrategy(), new OllamaClient()));
    
    const GameConfig config(players, 6, true);
    BlackjackGame game(config);
    for (int i = 0; i < 10; i++) {
        game.play();
        game.logGameResult(i+1);
        game.reset();
    }
    game.writeResultsToFile();

    // Clean up players
    for (Player* player : players) {
        delete player;
    }

    return 0;
}
