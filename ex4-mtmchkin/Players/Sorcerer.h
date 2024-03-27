#pragma once
#include "Job.h"

/**
 * Representation of a player of type sorcerer
*/
class Sorcerer : public Job{
public:
    /**
     * Constructor of Sorcerer
     *
     * @param name the name of the player
     * @param hp the maximum health points
     * @param level level of the player
     * @param force force of the player
     * @param coins starting coins amount
     * @param behavior the behavior type of the player
    */
    Sorcerer(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior);

    /**
     * Applies the solar eclipse card on the sorcerer
    */
    void applySolarEclipse() override;
};