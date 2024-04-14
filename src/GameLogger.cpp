#include "GameLogger.h"

void GameLogger::logGameResult(int gameID, const Dealer& dealer, const std::vector<Player>& players, bool isPlus3) {
    json result;
    result["gameID"] = gameID;
    result["isPlus3"] = isPlus3;

    json dealerJson;
    dealerJson["final_hand"] = dealer.getHandValue();
    std::vector<std::string> dealerCards;
    for (const auto& card : dealer.getHand()) {
        dealerCards.push_back(card.toString());
    }
    dealerJson["cards"] = dealerCards;
    result["dealer"] = dealerJson;

    std::vector<json> playersJson;
    for (const auto& player : players) {
        json playerJson;
        playerJson["final_hand"] = player.getHandValue();
        std::vector<std::string> cards;
        for (const auto& card : player.getHand()) {
            cards.push_back(card.toString());
        }
        playerJson["cards"] = cards;
        playerJson["main_outcome"] = player.getOutcome();
        playerJson["main_bet"] = player.getCurBet();
        if (isPlus3) {
            playerJson["side_outcome"] = player.getSideOutcome();
            playerJson["side_bet"] = player.getCurSideBet();
        } else {
            playerJson["side_outcome"] = "";
            playerJson["side_bet"] = 0;
        }
        playerJson["chips"] = player.getChips();
        playersJson.push_back(playerJson);
    }
    result["players"] = playersJson;

    resultsBuffer.push_back(result);
}

void GameLogger::writeResultsToFile(const std::string& filename) {
    json output = {{"data", resultsBuffer}};
    std::ofstream file(filename, std::ios::app | std::ios::out);
    file << output.dump(4);
    file.close();
}