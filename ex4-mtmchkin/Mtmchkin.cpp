
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

void Mtmchkin::playTurn(Job& player){
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Draw a card from the deck
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the card
     * 4. Print the turn outcome with "printTurnOutcome"
    */
    std::shared_ptr<Card> drawnCard = m_deck.drawCard();

    printTurnDetails(m_turnIndex, player, *drawnCard);

    int result = drawnCard->playCard(player);
    m_deck.insertBack(drawnCard);

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

    m_turnIndex++;
}

void Mtmchkin::playRound() {
    printRoundStart();

    for (auto player : m_players){
        if (player->getHealthPoints().isAlive()){
            playTurn(*player);
        }
    }

    printRoundEnd();
    printLeaderBoardMessage();
    
    const vector<shared_ptr<Job>>& leaderBoard = m_leaderBoard.getPlayers();
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
        if (player->getHealthPoints().isAlive()){
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

    Job& top = *m_leaderBoard.getTop();
    if (top.isMaxedOut()){
        printWinner(top);
    }
    else{
        printNoWinners();
    }
}
