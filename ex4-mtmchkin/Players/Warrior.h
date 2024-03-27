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
     * @param hp the maximum health points
     * @param level level of the player
     * @param force force of the player
     * @param coins starting coins amount
     * @param behavior the behavior type of the player
    */
    Warrior(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior);

    /**
     * Calculates the combat power of the warrior
     *
     * @return the combat power
    */
    virtual int calculateCombatPower() const override;
};
