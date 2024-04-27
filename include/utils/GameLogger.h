#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include <string>
#include <vector>
#include <fstream>
#include "Dealer.h"
#include "Player.h"
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;


class GameLogger {
public:
    void logGameResult(int gameID, const Dealer& dealer, std::vector<Player*>& players, bool isPlus3);
    void writeResultsToFile(const std::string& filename);
private:
    json resultsBuffer;
};

#endif // GAMELOGGER_H
