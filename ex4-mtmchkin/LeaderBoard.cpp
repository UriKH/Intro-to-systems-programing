#include <algorithm>
#include <vector>
#include "LeaderBoard.h"

using std::shared_ptr;

LeaderBoard::LeaderBoard(const std::vector<std::shared_ptr<Player>>& players) : m_players(players){}

bool comparePlayers(const shared_ptr<Player> player1, const shared_ptr<Player> player2);

void LeaderBoard::insert(const shared_ptr<Player> player){
    m_players.push_back(player);
    std::sort(m_players.begin(), m_players.end(), comparePlayers);
}

const std::shared_ptr<Player> LeaderBoard::getTop() const{
    return m_players[m_players.size() - 1];
}

const std::vector<shared_ptr<Player>>& LeaderBoard::getPlayers(){
    return m_players;
}

bool comparePlayers(const std::shared_ptr<Player> player1, const std::shared_ptr<Player> player2){
    if (player1->getLevel() != player2->getLevel()){
        return player1->getLevel() > player2->getLevel();
    }

    if (player1->getCoins() != player2->getCoins()){
        return player1->getCoins() > player2->getCoins();
    }

    return player1->getName() > player2->getName();
}