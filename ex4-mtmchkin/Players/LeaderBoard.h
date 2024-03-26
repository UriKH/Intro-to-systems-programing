#pragma once

#include <vector>
#include <memory>
#include "Player.h"

class LeaderBoard{
public:
    typedef bool (*SortingMethod)(const std::shared_ptr<Player>, const std::shared_ptr<Player>);
private:
    std::vector<std::shared_ptr<Player>> m_players;
    SortingMethod m_sortingMethod;

    static bool defaultSort(const std::shared_ptr<Player> player1, const std::shared_ptr<Player> player2);
public:
    LeaderBoard(SortingMethod method = defaultSort);
    LeaderBoard(const std::vector<std::shared_ptr<Player>>& players, SortingMethod method = defaultSort);

    /**
     * insert a new player into the leader board
     * @param player - the new player to add
    */
    void insert(const std::shared_ptr<Player> player);

    /**
     * gets the player at the currently winning player
     * @returns - the top player
    */
    const std::shared_ptr<Player> getTop() const;

    /**
     * gets all the players from the leader board
     * @returns - a list of the players sorted by place
    */
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;
};