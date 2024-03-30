#pragma once
#include "Job.h"
#include "Player.h"

/**
 * Representation of a player of type sorcerer
*/
class Sorcerer : public Job{
public:
    /**
     * Constructor of Sorcerer
     *
     * @param name the name of the player
     * @param behavior the behavior type of the player
    */
    explicit Sorcerer();

    /**
     * Applies the solar eclipse card on the Player
     *
     * @param player The player to apply the card
     * @return the amount of force given to the player (may be negative)
    */
    virtual int applySolarEclipse(Player& player) override;
};