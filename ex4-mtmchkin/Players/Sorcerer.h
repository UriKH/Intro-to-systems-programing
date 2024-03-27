#pragma once
#include "Job.h"

/**
 * Representation of a player of type sorcerer
*/
class Sorcerer : public Job{
public:
    /**
     * Calculates the combat power of the sorcerer
     * @return the combat power
    */
    Sorcerer(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior);

    /**
     * Retrive the type of the player
     * @return the name of the type
    */
    virtual std::string getJobName() const override;
};