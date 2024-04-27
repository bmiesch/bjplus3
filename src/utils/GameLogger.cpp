#include "GameLogger.h"

void GameLogger::logGameResult(int gameID, const Dealer& dealer, std::vector<Player*>& players, bool isPlus3) {
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
    for (auto& player : players) {
        json playerJson;
        if (isPlus3) {
            playerJson["side_outcome"] = player->getHand(0)->getSideOutcome();
            playerJson["side_bet"] = player->getHand(0)->getSideBet();
        } else {
            playerJson["side_outcome"] = "";
            playerJson["side_bet"] = 0;
        }
        playerJson["bankroll"] = player->getBankroll();

        std::vector<json> handsJson;
        for (int handIndex = 0; handIndex < player->getNumHands(); ++handIndex) {
            json handJson;
            handJson["final_hand"] = player->getHand(handIndex)->getValue();
            std::vector<std::string> cards;
            for (const auto& card : player->getHand(handIndex)->getCards()) {
                cards.push_back(card.toString());
            }
            handJson["cards"] = cards;
            handJson["main_outcome"] = player->getHand(handIndex)->getOutcome();
            handJson["main_bet"] = player->getHand(handIndex)->getBet();
            handsJson.push_back(handJson);
        }
        playerJson["hands"] = handsJson;
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