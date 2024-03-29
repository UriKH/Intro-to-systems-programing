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
    Warrior(const std::string& name, std::shared_ptr<Behavior> behavior);

    /**
     * Calculates the combat power of the warrior
     *
     * @return the combat power
    */
    virtual int calculateCombatPower() const override;

    int applyEncounter(const Encounter& monster) override;
};
