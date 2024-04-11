#include "BlackjackGame.h"
#include <iostream>
#include <algorithm>

BlackjackGame::BlackjackGame(int numPlayers, int numDecks, bool isPlus3) : fullDeck(numDecks), dealer(), isPlus3(isPlus3) {
    for(int i = 0; i < numPlayers; i++) {
        players.push_back(Player());
    }
    fullDeck.shuffle();
}

Card BlackjackGame::getCard() {
    return fullDeck.drawCard();
}

void BlackjackGame::getBets() {
    for (int i = 0; i < players.size(); i++) {
        std::cout << "Player " << i << ": How much would you like to bet?" << std::endl;
        int bet;
        std::cin >> bet;
        players[i].setCurBet(bet);
        
        if (isPlus3) {
            std::cout << "How much would you like to side bet?" << std::endl;
            int sideBet;
            std::cin >> sideBet;
            players[i].setCurSideBet(sideBet);
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

    // Deal cards to dealer if not all players are busted
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
        } else if (!playerBusted && playerValue > dealerValue) {
            std::cout << "Player wins " << player.getCurBet() << " chips!" << std::endl;
            player.addChips(player.getCurBet());
        } else if (!playerBusted && playerValue == dealerValue) {
            std::cout << "Player ties!" << std::endl;
        } else {
            std::cout << "Player loses " << player.getCurBet() << " chips!" << std::endl;
            player.removeChips(player.getCurBet());
        }

        player.reset();
    }
    for (std::size_t i = 0; i < players.size(); ++i) {
        std::cout << "Player " << i << " has " << players[i].getChips() << " chips" << std::endl;
    }

    dealer.reset();
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
        std::cout << "Player card 1: " << playerCard1 << std::endl;
        std::cout << "Player card 2: " << playerCard2 << std::endl;
        std::cout << "Dealer card: " << dealerUpCard << std::endl;

        if ((playerCard1.getRank() == dealerUpCard.getRank() && playerCard2.getRank() == dealerUpCard.getRank())
            || (playerCard1.getSuit() == dealerUpCard.getSuit() && playerCard2.getSuit() == dealerUpCard.getSuit())
            || (isStraight(playerCard1, playerCard2, dealerUpCard))) {

            // Plus3 pays 9 to 1 on the side bet
            std::cout << "Side Bet: Player wins " << player.getCurSideBet() * 9 << " chips!" << std::endl;
            player.addChips(player.getCurSideBet() * 9);
        }
        else {
            std::cout << "Side Bet: Player loses " << player.getCurSideBet() << " chips!" << std::endl;
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