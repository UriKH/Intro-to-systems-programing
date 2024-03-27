#pragma once
#include "Job.h"

/**
 * Representation of a player of type warrior
*/
class Warrior : public Job{
public:
    Warrior(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior);

    /**
     * Calculates the combat power of the warrior
     * @return the combat power
    */
    virtual int calculateCombatPower() const override;

    /**
     * Retrive the type of the player
     * @return the name of the type
    */
    virtual std::string getJobName() const override;
};
