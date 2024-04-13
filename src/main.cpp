#include "BlackjackGame.h"

int main() {
    BlackjackGame game(1, 6, true, true);
    for (int i = 0; i < 10; i++) {
        game.play();
        game.logGameResult(i+1);
        game.reset();
    }
    game.writeResultsToFile();
    return 0;
}
