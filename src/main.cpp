#include "BlackjackGame.h"
#include <memory>

int main() {
    std::vector<Player*> players;
    players.push_back(new Player(1, 100, new ConsBetStrategy(), new BasicStrategy()));
    players.push_back(new Player(2, 100, new AggrBetStrategy(), new BasicStrategy()));
    
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
