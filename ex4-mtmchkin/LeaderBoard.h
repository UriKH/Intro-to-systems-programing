#pragma once

#include <vector>
#include <memory>
#include "Players/Player.h"

class LeaderBoard{
    std::vector<std::shared_ptr<Player>> m_players;
public:
    LeaderBoard() = default;

    /**
     * Constructor of LeaderBoard
     *
     * @param players list of players in the leadboard
     * @param method the sorting method to sort the leader board by
    */
    LeaderBoard(const std::vector<std::shared_ptr<Player>>& players);

    /**
     * insert a new player into the leader board
     *
     * @param player the new player to add
    */
    void insert(const std::shared_ptr<Player> player);

    /**
     * gets the player at the currently winning player
     *
     * @returns the top player
    */
    const std::shared_ptr<Player> getTop();

    /**
     * gets all the players from the leader board
     *
     * @returns a list of the players sorted by place
    */
    const std::vector<std::shared_ptr<Player>>& getPlayers();
};