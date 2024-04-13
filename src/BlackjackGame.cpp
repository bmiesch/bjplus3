#include "BlackjackGame.h"


BlackjackGame::BlackjackGame(int numPlayers, int numDecks, bool isPlus3, bool standardBets)
    : fullDeck(numDecks), dealer(), isPlus3(isPlus3), standardBets(standardBets) {
    for(int i = 0; i < numPlayers; i++) {
        players.push_back(Player());
    }
    fullDeck.shuffle();
}

Card BlackjackGame::getCard() {
    return fullDeck.drawCard();
}

int BlackjackGame::askForBet(const std::string& prompt) {
    std::cout << prompt << std::endl;
    int bet;
    while (!(std::cin >> bet)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return bet;
}

void BlackjackGame::getBets() {
    for (auto& player : players) {
        int bet = standardBets ? 10 : askForBet("How much would you like to bet?");
        player.setCurBet(bet);

        if (isPlus3) {
            int sideBet = standardBets ? 5 : askForBet("How much would you like to side bet?");
            player.setCurSideBet(sideBet);
        }
    }
}

void BlackjackGame::dealInitialRound() {
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < players.size(); j++) {
            players[j].addCard(fullDeck.drawCard());
        }
        dealer.addCard(fullDeck.drawCard());
    }
}

void BlackjackGame::dealRound() {
    bool allPlayersBusted = true;

    for (auto& player : players) {
        while (player.getHandValue() < 17) {
            player.addCard(fullDeck.drawCard());
        }

        if (player.getHandValue() > 21) {
            player.setBusted(true);
            std::cout << "Player busted!" << std::endl;
        } else {
            allPlayersBusted = false;
            std::cout << "Player has " << player.getHandValue() << std::endl;
        }
    }

    if (!allPlayersBusted) {
        dealCardsToDealer();
    } else {
        std::cout << "All players busted!" << std::endl;
    }
}

void BlackjackGame::dealCardsToDealer() {
    int dealerValue = dealer.getHandValue();
    while (dealerValue < 17) {
        dealer.addCard(fullDeck.drawCard());
        dealerValue = dealer.getHandValue();
    }

    if (dealerValue > 21) {
        dealer.setBusted(true);
        std::cout << "Dealer busted!" << std::endl;
    } else {
        std::cout << "Dealer has " << dealerValue << std::endl;
    }
}

void BlackjackGame::finishRound() {
    std::cout << "---------------" << std::endl;
    int dealerValue = dealer.getHandValue();
    bool dealerBusted = dealer.isBusted();

    for (auto& player : players) {
        int playerValue = player.getHandValue();
        bool playerBusted = player.isBusted();

        if (dealerBusted && !playerBusted) {
            std::cout << "Player wins " << player.getCurBet() << " chips!" << std::endl;
            player.addChips(player.getCurBet());
            player.setOutcome("win");
        } else if (!playerBusted && playerValue > dealerValue) {
            std::cout << "Player wins " << player.getCurBet() << " chips!" << std::endl;
            player.addChips(player.getCurBet());
            player.setOutcome("win");
        } else if (!playerBusted && playerValue == dealerValue) {
            std::cout << "Player ties!" << std::endl;
            player.setOutcome("tie");
        } else {
            std::cout << "Player loses " << player.getCurBet() << " chips!" << std::endl;
            player.removeChips(player.getCurBet());
            player.setOutcome("lose");
        }
    }
    for (std::size_t i = 0; i < players.size(); ++i) {
        std::cout << "Player " << i << " has " << players[i].getChips() << " chips" << std::endl;
    }
}

bool BlackjackGame::isStraight(Card card1, Card card2, Card card3) {
    std::vector<Card::Rank> ranks = {card1.getRank(), card2.getRank(), card3.getRank()};
    std::sort(ranks.begin(), ranks.end());
    return (ranks[1] == ranks[0] + 1) && (ranks[2] == ranks[1] + 1);
}

void BlackjackGame::plus3Check() {
    Card dealerUpCard = dealer.getUpCard();
    for (auto& player : players) {
        Card playerCard1 = player.getHand()[0];
        Card playerCard2 = player.getHand()[1];

        if ((playerCard1.getRank() == dealerUpCard.getRank() && playerCard2.getRank() == dealerUpCard.getRank())
            || (playerCard1.getSuit() == dealerUpCard.getSuit() && playerCard2.getSuit() == dealerUpCard.getSuit())
            || (isStraight(playerCard1, playerCard2, dealerUpCard))) {

            // Plus3 pays 9 to 1 on the side bet
            std::cout << "Side Bet: Player wins " << player.getCurSideBet() * 9 << " chips!" << std::endl;
            player.setSideOutcome("win");
            player.addChips(player.getCurSideBet() * 9);
        }
        else {
            std::cout << "Side Bet: Player loses " << player.getCurSideBet() << " chips!" << std::endl;
            player.setSideOutcome("lose");
            player.removeChips(player.getCurSideBet());
        }
    }
}

void BlackjackGame::play() {
    getBets();
    dealInitialRound();
    if (isPlus3) {
        plus3Check();
    }
    dealRound();
    finishRound();
}

void BlackjackGame::reset() {
    for (auto& player : players) {
        player.reset();
    }
    dealer.reset();
}


void BlackjackGame::logGameResult(int gameID) {
    json result;

    // Basic game information
    result["gameID"] = gameID;
    result["isPlus3"] = isPlus3;

    // Dealer information
    json dealerJson;
    dealerJson["final_hand"] = dealer.getHandValue();
    std::vector<std::string> dealerCards;
    for (auto& card : dealer.getHand()) {
        dealerCards.push_back(card.toString());
    }
    dealerJson["cards"] = dealerCards;
    result["dealer"] = dealerJson;

    // Players information
    std::vector<nlohmann::ordered_json> playersJson;
    for (auto& player : players) {
        nlohmann::ordered_json playerJson;
        playerJson["final_hand"] = player.getHandValue();
        std::vector<std::string> cards;
        for (auto& card : player.getHand()) {
            cards.push_back(card.toString());
        }
        playerJson["cards"] = cards;
        playerJson["main_outcome"] = player.getOutcome();
        playerJson["main_bet"] = player.getCurBet();
        if (isPlus3) {
            playerJson["side_outcome"] = player.getSideOutcome();
            playerJson["side_bet"] = player.getCurSideBet();
        }
        else {
            playerJson["side_outcome"] = "";
            playerJson["side_bet"] = 0;
        }
        playerJson["chips"] = player.getChips();
        playersJson.push_back(playerJson);
    }
    result["players"] = playersJson;

    // Write to buffer
    resultsBuffer.push_back(result);
}

void BlackjackGame::writeResultsToFile() {
    json output = {{"data", resultsBuffer}};
    std::ofstream file("game_results.json", std::ios::app | std::ios::out);
    file << output.dump(4);
    file.close();
}

