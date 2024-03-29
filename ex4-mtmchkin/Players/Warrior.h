#pragma once
#include "Job.h"

/**
 * Representation of a player of type warrior
*/
class Warrior : public Job{
public:
    /**
     * Constructor of Warrior
     *
     * @param name the name of the player
     * @param behavior the behavior type of the player
    */
    Warrior();

    /**
     * Calculates the combat power of the warrior
     *
     * @return the combat power
    */
    virtual int calculateCombatPower(Player& player) const override;

    int applyEncounter(Player& player, const Encounter& monster) override;
};
