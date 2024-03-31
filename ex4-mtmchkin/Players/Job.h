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
     * @param player The player to apply the card
     * @return the combat power
    */
    virtual int calculateCombatPower(Player& player) const;

    /**
     * Applies the solar eclipse card on the Player
     *
     * @param player The player to apply the card
     * @param monster The monster stats the player encounters
     * @return the damage dealt if player lost and the loot the player found if battle won
    */
    virtual int applyEncounter(Player& player, const Encounter& monster);

    /**
     * Applies the solar eclipse card on the Player
     *
     * @param player The player to apply the card
     * @return the amount of force given to the player (may be negative)
    */
    virtual int applySolarEclipse(Player& player);

    /**
     * Applies the solar eclipse card on the Player
     *
     * @param player The player to apply the card
     * @return the amount of potions bought
    */
    virtual int applyPotionsMerchant(Player& player);

    /**
     * Gets the name of the job
     *
     * @param the name of the job
    */
    virtual std::string getName() const;
};