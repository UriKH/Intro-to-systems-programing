#pragma once

#include <string>
#include <memory>

class Encounter;
class Player;

//TODO

class Job{
protected:
    std::string m_jobTitle;
    
    Job(const std::string& jobTitle);
public:
    /**
     * Calculates the combat power of the warrior
     *
     * @return the combat power
    */
    virtual int calculateCombatPower(Player&) const;

    /**
     * Applies the solar eclipse card on the Player
    */
    virtual int applyEncounter(Player&, const Encounter& monster);

    /**
     * Applies the solar eclipse card on the Player
    */
    virtual int applySolarEclipse(Player&);

    /**
     * Applies the solar eclipse card on the Player
    */
    virtual int applyPotionsMerchant(Player&);

    /**
     * creates a string representaion of the player
     *
     * @return the player's string representation
    */
    // virtual std::string getDescription() const override;
};