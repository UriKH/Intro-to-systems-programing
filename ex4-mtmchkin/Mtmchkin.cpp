
#include "Mtmchkin.h"
#include "utilities.h"
#include "Cards/Event.h"
#include "Parser.h"

#include <memory>

using std::shared_ptr;
using std::vector;
using std::string;

Mtmchkin::Mtmchkin(const string& deckPath, const string& playersPath){
    Parser::parseCards(deckPath, m_deck);
    Parser::parsePlayers(playersPath, m_players);
    m_leaderBoard = LeaderBoard(m_players);
    this->m_turnIndex = 1;
}

#include <iostream>

void Mtmchkin::playTurn(Player& player){
    std::unique_ptr<Card> drawnCard = m_deck.drawCard();

    printTurnDetails(m_turnIndex, player, *drawnCard);
    int result = drawnCard->playCard(player);

    if (drawnCard->getName() == SolarEclipse().getName()){
        printTurnOutcome(getSolarEclipseMessage(player, result));
    }
    else if (drawnCard->getName() == PotionsMerchant().getName()){
        printTurnOutcome(getPotionsPurchaseMessage(player, result));
    }
    else{
        if (result < 0){
            printTurnOutcome(getEncounterLostMessage(player, -result));
        }
        else{
            printTurnOutcome(getEncounterWonMessage(player, result));
        }
    }

    m_deck.insertCard(std::move(drawnCard));
    m_turnIndex++;
}

void Mtmchkin::playRound() {
    printRoundStart();

    for (auto player : m_players){
        if (player->getHealthPoints() > HealthPoints::MIN_HP){
            playTurn(*player);
        }
    }

    printRoundEnd();
    printLeaderBoardMessage();
    
    const vector<shared_ptr<Player>>& leaderBoard = m_leaderBoard.getPlayers();
    for (size_t i = 1; i <= leaderBoard.size(); i++){
        printLeaderBoardEntry(i, *leaderBoard[i-1]);
    }
    
    printBarrier();
}

bool Mtmchkin::isGameOver(){
    if (m_leaderBoard.getTop()->isMaxedOut()){
        return true;
    }

    for (auto player : m_players){
        if (player->getHealthPoints() > HealthPoints::MIN_HP){
            return false;
        }
    }
    return true;
}

void Mtmchkin::play() {
    printStartMessage();
    for (size_t i = 1; i <= m_players.size(); i++){
        printStartPlayerEntry(i, *m_players[i-1]);
    }

    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();

    Player& top = *m_leaderBoard.getTop();
    if (top.isMaxedOut()){
        printWinner(top);
    }
    else{
        printNoWinners();
    }
}
