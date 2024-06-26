#include "BlackjackGame.h"


BlackjackGame::BlackjackGame(const GameConfig& config)
    : fullDeck(config.numDecks), dealer(), config(config) {
    fullDeck.shuffle();
}

void BlackjackGame::dealInitialRound() {
    for (auto& player : config.players) {
        for (int i = 0; i < player->getInitialNumHands(); i++) {
            player->createHand(player->makeBet());

            if (config.isPlus3) {
                Hand* curHand = player->getHand(i);
                curHand->setSideBet(player->makeSideBet());
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        for (auto& player : config.players) {
            for (int i = 0; i < player->getInitialNumHands(); i++) {
                player->getHand(i)->addCard(fullDeck.drawCard());
            }
        }
        dealer.addCard(fullDeck.drawCard());
    }

    for (std::size_t i = 0; i < config.players.size(); ++i) {
        for (size_t handIndex = 0; handIndex < config.players[i]->getNumHands(); ++handIndex) {
            std::cout << "Player " << i << " hand " << handIndex + 1 << " has: ";
            for (auto& card : config.players[i]->getHand(handIndex)->getCards()) {
                std::cout << card.toString() << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Dealer has " << dealer.getHand()[0].toString() << " and a hidden card" << std::endl;
}

void BlackjackGame::dealRound() {
    bool allHandsBusted = true;

    for (auto& player : config.players) {
        size_t handIndex = 0;
        while (handIndex < player->getNumHands()) {
            Hand* curHand = player->getHand(handIndex);
            bool isStanding = false;

            while(!curHand->isBusted() && curHand->getValue() < 21 && !isStanding) {
                Card dealerUpCard = dealer.getUpCard();
                bool canSplit = false;
                PlayerAction action = player->act(handIndex, dealerUpCard, canSplit);

                switch (action) {
                    case PlayerAction::HIT:
                        std::cout << "Player " << player->getId() << " hits on hand " << handIndex + 1 << "!" << std::endl;
                        curHand->addCard(fullDeck.drawCard());
                        break;
                    case PlayerAction::STAND:
                        std::cout << "Player " << player->getId() << " stands on hand " << handIndex + 1 << "!" << std::endl;
                        isStanding = true;
                        break;
                    case PlayerAction::DOUBLE_DOWN:
                        std::cout << "Player " << player->getId() << " doubles down on hand " << handIndex + 1 << "!" << std::endl;
                        curHand->addCard(fullDeck.drawCard());
                        curHand->setBet(curHand->getBet() * 2);
                        isStanding = true;
                        break;
                    case PlayerAction::SPLIT:
                        std::cout << "Player " << player->getId() << " splits hand " << handIndex + 1 << "!" << std::endl;
                        player->splitHand(handIndex);
                        curHand->addCard(fullDeck.drawCard());
                        player->getHand(handIndex + 1)->addCard(fullDeck.drawCard());
                        break;
                }
            }

            if (curHand->getValue() > 21) {
                curHand->setBusted(true);
                std::cout << "Player " << player->getId() << " hand " << handIndex + 1 << " busted!" << std::endl;
            } else {
                allHandsBusted = false;
                std::cout << "Player " << player->getId() << " hand " << handIndex + 1 << " is " << curHand->getValue() << std::endl;
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
        for (size_t handIndex = 0; handIndex < player->getNumHands(); ++handIndex) {
            int playerValue = player->getHand(handIndex)->getValue();
            bool playerBusted = player->getHand(handIndex)->isBusted();

            int numHands = player->getNumHands();
            Hand* curHand = player->getHand(handIndex);
            int curBet = curHand->getBet();

            if (dealerBusted && !playerBusted) {
                std::cout << "Player " << player->getId() << " | " << handIndex + 1 << "/" << numHands << " | +" << curBet << std::endl;
                player->updateBankroll(curBet);
                curHand->setOutcome("win");
            } else if (!playerBusted && playerValue > dealerValue) {
                std::cout << "Player " << player->getId() << " | " << handIndex + 1 << "/" << numHands << " | +" << curBet << std::endl;
                player->updateBankroll(curBet);
                curHand->setOutcome("win");
            } else if (!playerBusted && playerValue == dealerValue) {
                std::cout << "Player " << player->getId() << " | " << handIndex + 1 << "/" << numHands << " | tie" << std::endl;
                curHand->setOutcome("tie");
            } else {
                std::cout << "Player " << player->getId() << " | " << handIndex + 1 << "/" << numHands << " | -" << curBet << std::endl;
                player->updateBankroll(-curBet);
                curHand->setOutcome("lose");
            }
        }
    }

    for (const auto& player : config.players) {
        std::cout << "Player " << player->getId() << " has " << player->getBankroll() << " chips" << std::endl;
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
        for (size_t handIndex = 0; handIndex < player->getNumHands(); ++handIndex) {
            const auto& cards = player->getHand(handIndex)->getCards();
            if (cards.size() < 2) continue; // Ensure there are at least two cards in the hand

            Card playerCard1 = cards[0];
            Card playerCard2 = cards[1];

            if ((playerCard1.getRank() == dealerUpCard.getRank() && playerCard2.getRank() == dealerUpCard.getRank())
                || (playerCard1.getSuit() == dealerUpCard.getSuit() && playerCard2.getSuit() == dealerUpCard.getSuit())
                || (isStraight(playerCard1, playerCard2, dealerUpCard))) {

                // Plus3 pays 9 to 1 on the side bet
                std::cout << "Side Bet: Player wins " << player->getHand(handIndex)->getSideBet() * 9 << " chips!" << std::endl;
                player->getHand(handIndex)->setSideOutcome("win");
                player->updateBankroll(player->getHand(handIndex)->getSideBet() * 9);
            } else {
                std::cout << "Side Bet: Player loses " << player->getHand(handIndex)->getSideBet() << " chips!" << std::endl;
                player->getHand(handIndex)->setSideOutcome("lose");
                player->updateBankroll(-player->getHand(handIndex)->getSideBet());
            }
        }
    }
}

void BlackjackGame::play() {
    dealInitialRound();
    if (config.isPlus3) {
        finishSideBet();
    }
    dealRound();
    finishRound();
}

void BlackjackGame::reset() {
    for (auto& player : config.players) {
        player->reset();
    }
    dealer.reset();
}

void BlackjackGame::logGameResult(int gameID) {
    logger.logGameResult(gameID, dealer, config.players, config.isPlus3);
}

void BlackjackGame::writeResultsToFile() {
    logger.writeResultsToFile("game_results.json");
}
