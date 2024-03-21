#include <algorithm>
#include <vector>
#include "LeadBoard.h"

using std::shared_ptr;

bool compare_players(const shared_ptr<Player> player1, const shared_ptr<Player> player2){
    if (player1->getLevel() != player2->getLevel()){
        return player1->getLevel() > player2->getLevel();
    }

    if (player1->getCoins() != player2->getCoins()){
        return player1->getCoins() > player2->getCoins();
    }

    return player1->getName() > player2->getName();
}

void LeadBoard::refresh(){
    std::sort(m_players.begin(), m_players.end(), compare_players);
}

void LeadBoard::insert(const shared_ptr<Player> player){
    m_players.push_back(player);
}

std::vector<shared_ptr<Player>> LeadBoard::getPlayers(){
    return m_players;
}