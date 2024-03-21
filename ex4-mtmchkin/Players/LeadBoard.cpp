#include <algorithm>
#include <vector>
#include "LeadBoard.h"

bool compare_players(const Player* const player1, const Player* const player2){
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

void LeadBoard::insert(const Player* const player){
    m_players.push_back(player);
}

std::vector<const Player*> LeadBoard::getPlayers(){
    return m_players;
}