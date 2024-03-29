#pragma once

#include <string>
#include <memory>
#include "Player.h"
// #include "../Cards/Encounter.h"

class Encounter;

//TODO

class Job : public Player{
protected:
    std::string m_jobTitle;
    
    Job(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior, const std::string& jobTitle);
public:
    /**
     * Calculates the combat power of the warrior
     *
     * @return the combat power
    */
    virtual int calculateCombatPower() const;

    /**
     * Applies the solar eclipse card on the Player
    */
    virtual int applyEncounter(const Encounter& monster);

    /**
     * Applies the solar eclipse card on the Player
    */
    virtual int applySolarEclipse();

    /**
     * Applies the solar eclipse card on the Player
    */
    virtual int applyPotionsMerchant();

    /**
     * creates a string representaion of the player
     *
     * @return the player's string representation
    */
    virtual std::string getDescription() const override;
};