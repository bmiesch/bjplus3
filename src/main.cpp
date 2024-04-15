#include "BlackjackGame.h"

int main() {
    std::vector<Player> players;
    players.push_back(Player(100, new ConsBetStrategy(), new BasicStrategy()));
    players.push_back(Player(100, new AggrBetStrategy(), new BasicStrategy()));
    const GameConfig config(players, 6, true);
    BlackjackGame game(config);
    for (int i = 0; i < 10; i++) {
        game.play();
        game.logGameResult(i+1);
        game.reset();
    }
    game.writeResultsToFile();
    return 0;
}
