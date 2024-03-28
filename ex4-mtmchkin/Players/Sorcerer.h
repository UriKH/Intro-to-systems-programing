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
     * @param behavior the behavior type of the player
    */
    Sorcerer(const std::string& name, std::shared_ptr<Behavior> behavior);

    /**
     * Applies the solar eclipse card on the sorcerer
    */
    void applySolarEclipse() override;
};