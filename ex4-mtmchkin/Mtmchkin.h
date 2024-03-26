
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "Player.h"
#include "LeaderBoard.h"
#include "CardDeck.h"

class Mtmchkin{
private:
    int m_turnIndex;
    std::vector<std::shared_ptr<Player>> m_players;
    LeaderBoard m_leaderBoard;
    CardDeck m_deck;

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
    Mtmchkin(const std::string& deckPath, const std::string& playersPath);

    /**
     * Plays the entire game
     * 
     * @return - void
    */
    void play();
};
