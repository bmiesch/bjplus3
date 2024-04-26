#include "BlackjackGame.h"


BlackjackGame::BlackjackGame(const GameConfig& config)
    : fullDeck(config.numDecks), dealer(), config(config) {
    fullDeck.shuffle();
}

// Card BlackjackGame::getCard() {
//     return fullDeck.drawCard();
// }

void BlackjackGame::getBets() {
    for (auto& player : config.players) {
        int bet = player.makeBet();

        if (config.isPlus3) {
            int sideBet = player.makeSideBet();
        }
    }
}

void BlackjackGame::dealInitialRound() {
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < config.players.size(); j++) {
            if (i == 0) {
                config.players[i].createHand(config.players[i].getCurBet());
            }
            config.players[j].getHand(0)->addCard(fullDeck.drawCard());
        }
        dealer.addCard(fullDeck.drawCard());
    }
    for (std::size_t i = 0; i < config.players.size(); ++i) {
        for (auto& card : config.players[i].getHand(0)->getCards()) {
            std::cout << "Player " << i << " has " << card.toString() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Dealer has " << dealer.getHand()[0].toString() << " and a hidden card" << std::endl;
}

void BlackjackGame::dealRound() {
    bool allHandsBusted = true;

    for (auto& player : config.players) {
        for (size_t handIndex = 0; handIndex < player.getNumHands(); ++handIndex) {
            bool isStanding = false;

            while (!player.getHand(handIndex)->isBusted() && player.getHand(handIndex)->getValue() < 21 && !isStanding) {
                Card dealerUpCard = dealer.getUpCard();
                bool canSplit = false;
                PlayerAction action = player.act(handIndex, dealerUpCard, canSplit);

                switch (action) {
                    case PlayerAction::HIT:
                        std::cout << "Player hits!" << std::endl;
                        player.getHand(handIndex)->addCard(fullDeck.drawCard());
                        break;
                    case PlayerAction::STAND:
                        std::cout << "Player stands!" << std::endl;
                        isStanding = true;
                        break;
                    case PlayerAction::DOUBLE_DOWN:
                        std::cout << "Player doubles down!" << std::endl;
                        player.getHand(handIndex)->addCard(fullDeck.drawCard());
                        player.getHand(handIndex)->setBet(player.getHand(handIndex)->getBet() * 2);
                        isStanding = true; 
                        break;
                    case PlayerAction::SPLIT:
                        // TODO: Handle split logic
                        break;
                }
            }

            if (player.getHand(handIndex)->getValue() > 21) {
                player.getHand(handIndex)->setBusted(true);
                std::cout << "Player busted!" << std::endl;
            } else {
                allHandsBusted = false;
                std::cout << "Player has " << player.getHand(handIndex)->getValue() << std::endl;
            }
        }
    }

    if (!allHandsBusted) {
        dealCardsToDealer();
    } else {
        std::cout << "All players busted!" << std::endl;
    }
}


void BlackjackGame::dealRound() {
    bool allHandsBusted = true;

    for (auto& player : config.players) {
        size_t handIndex = 0;
        while (handIndex < player.getNumHands()) {
            Hand* curHand = player.getHand(handIndex);
            bool isStanding = false;

            while(!curHand->isBusted() && curHand->getValue() < 21 && !isStanding) {
                Card dealerUpCard = dealer.getUpCard();
                bool canSplit = false;
                PlayerAction action = player.act(handIndex, dealerUpCard, canSplit);

                switch (action) {
                    case PlayerAction::HIT:
                        std::cout << "Player hits on hand " << handIndex + 1 << "!" << std::endl;
                        curHand->addCard(fullDeck.drawCard());
                        break;
                    case PlayerAction::STAND:
                        std::cout << "Player stands on hand " << handIndex + 1 << "!" << std::endl;
                        isStanding = true;
                        break;
                    case PlayerAction::DOUBLE_DOWN:
                        std::cout << "Player doubles down on hand " << handIndex + 1 << "!" << std::endl;
                        curHand->addCard(fullDeck.drawCard());
                        curHand->setBet(curHand->getBet() * 2);
                        isStanding = true;
                        break;
                    case PlayerAction::SPLIT:
                        std::cout << "Player splits hand " << handIndex + 1 << "!" << std::endl;
                        player.splitHand(handIndex); // This function needs to handle the logic of splitting
                        curHand->addCard(fullDeck.drawCard());
                        player.getHand(handIndex + 1)->addCard(fullDeck.drawCard());
                        break;
                }
            }

            if (curHand->getValue() > 21) {
                curHand->setBusted(true);
                std::cout << "Player's hand " << handIndex + 1 << " busted!" << std::endl;
            } else {
                allHandsBusted = false;
                std::cout << "Player's hand " << handIndex + 1 << " has " << curHand->getValue() << std::endl;
            }

            handIndex++;
        }
    }

    if (!allHandsBusted) {
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

    for (auto& player : config.players) {
        int playerValue = player.getHandValue();
        bool playerBusted = player.isBusted();

        if (dealerBusted && !playerBusted) {
            std::cout << "Player wins " << player.getCurBet() << " chips!" << std::endl;
            player.updateBankroll(player.getCurBet());
            player.setOutcome("win");
        } else if (!playerBusted && playerValue > dealerValue) {
            std::cout << "Player wins " << player.getCurBet() << " chips!" << std::endl;
            player.updateBankroll(player.getCurBet());
            player.setOutcome("win");
        } else if (!playerBusted && playerValue == dealerValue) {
            std::cout << "Player ties!" << std::endl;
            player.setOutcome("tie");
        } else {
            std::cout << "Player loses " << player.getCurBet() << " chips!" << std::endl;
            player.updateBankroll(-player.getCurBet());
            player.setOutcome("lose");
        }
    }
    for (std::size_t i = 0; i < config.players.size(); ++i) {
        std::cout << "Player " << i << " has " << config.players[i].getBankroll() << " chips" << std::endl;
    }
}

bool BlackjackGame::isStraight(Card card1, Card card2, Card card3) {
    std::vector<Card::Rank> ranks = {card1.getRank(), card2.getRank(), card3.getRank()};
    std::sort(ranks.begin(), ranks.end());
    return (ranks[1] == ranks[0] + 1) && (ranks[2] == ranks[1] + 1);
}

void BlackjackGame::finishSideBet() {
    Card dealerUpCard = dealer.getUpCard();
    for (auto& player : config.players) {
        Card playerCard1 = player.getHand()[0];
        Card playerCard2 = player.getHand()[1];

        if ((playerCard1.getRank() == dealerUpCard.getRank() && playerCard2.getRank() == dealerUpCard.getRank())
            || (playerCard1.getSuit() == dealerUpCard.getSuit() && playerCard2.getSuit() == dealerUpCard.getSuit())
            || (isStraight(playerCard1, playerCard2, dealerUpCard))) {

            // Plus3 pays 9 to 1 on the side bet
            std::cout << "Side Bet: Player wins " << player.getCurSideBet() * 9 << " chips!" << std::endl;
            player.setSideOutcome("win");
            player.updateBankroll(player.getCurSideBet() * 9);
        }
        else {
            std::cout << "Side Bet: Player loses " << player.getCurSideBet() << " chips!" << std::endl;
            player.setSideOutcome("lose");
            player.updateBankroll(-player.getCurSideBet());
        }
    }
}

void BlackjackGame::play() {
    getBets();
    dealInitialRound();
    if (config.isPlus3) {
        finishSideBet();
    }
    dealRound();
    finishRound();
}

void BlackjackGame::reset() {
    for (auto& player : config.players) {
        player.reset();
    }
    dealer.reset();
}

void BlackjackGame::logGameResult(int gameID) {
    logger.logGameResult(gameID, dealer, config.players, config.isPlus3);
}

void BlackjackGame::writeResultsToFile() {
    logger.writeResultsToFile("game_results.json");
}
