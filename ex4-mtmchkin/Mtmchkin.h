
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "Players/Player.h"
#include "Cards/Card.h"

using std::string;
using std::shared_ptr;
using std::vector;
using std::queue;

class Mtmchkin{
private:
    int m_turnIndex;

    /**
     * Playes a single turn for a player
     * 
     * @param player - the player to play the turn for
     * 
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     * 
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     * 
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of Mtmchkin class
     * 
     * @param deckPath - path to the deck file
     * @param playersPath - path to the players file
     * 
     * @return - Mtmchkin object with the given deck and players
     *
    */
    Mtmchkin(const string& deckPath, const string& playersPath);

    /**
     * Plays the entire game
     * 
     * @return - void
    */
    void play();
};
