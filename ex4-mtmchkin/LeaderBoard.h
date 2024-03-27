#pragma once

#include <vector>
#include <memory>
#include "Players/Player.h"

class LeaderBoard{
public:
    // defines the prototype of a table sorting method
    typedef bool (*SortingMethod)(const std::shared_ptr<Player>, const std::shared_ptr<Player>);
private:
    std::vector<std::shared_ptr<Player>> m_players;
    SortingMethod m_sortingMethod;

    /**
     * Default sorting method of the leader board
     * @param palyer1 the first player to compare
     * @param player2 the second player to compare
     * @returns true if the first player is in an upper place than the second
    */
    static bool defaultSort(const std::shared_ptr<Player> player1, const std::shared_ptr<Player> player2){
        if (player1->getLevel() != player2->getLevel()){
            return player1->getLevel() > player2->getLevel();
        }

        if (player1->getCoins() != player2->getCoins()){
            return player1->getCoins() > player2->getCoins();
        }

        return player1->getName() > player2->getName();
    }
public:
    LeaderBoard(SortingMethod method = defaultSort);
    
    LeaderBoard(const std::vector<std::shared_ptr<Player>>& players, SortingMethod method = defaultSort);

    /**
     * insert a new player into the leader board
     * @param player the new player to add
    */
    void insert(const std::shared_ptr<Player> player);

    /**
     * gets the player at the currently winning player
     * @returns the top player
    */
    const std::shared_ptr<Player> getTop() const;

    /**
     * gets all the players from the leader board
     * @returns a list of the players sorted by place
    */
    const std::vector<std::shared_ptr<Player>>& getPlayers();
};