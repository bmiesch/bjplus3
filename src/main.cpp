#include "BlackjackGame.h"

int main() {
    const GameConfig config(1, 6, true, true);
    BlackjackGame game(config);
    for (int i = 0; i < 10; i++) {
        game.play();
        game.logGameResult(i+1);
        game.reset();
    }
    game.writeResultsToFile();
    return 0;
}
