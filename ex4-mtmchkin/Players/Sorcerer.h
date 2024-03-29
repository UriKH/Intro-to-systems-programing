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
    Sorcerer();

    /**
     * Applies the solar eclipse card on the sorcerer
    */
    virtual int applySolarEclipse(Player&) override;
};