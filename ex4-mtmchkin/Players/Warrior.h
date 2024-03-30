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
    explicit Warrior();

    /**
     * Calculates the combat power of the warrior
     *
     * @return the combat power
    */
    virtual int calculateCombatPower(Player& player) const override;

    /**
     * Applies the solar eclipse card on the Player
     *
     * @param player The player to apply the card
     * @param monster The monster stats the player encounters
     * @return the damage dealt if player lost and the loot the player found if battle won
    */
    virtual int applyEncounter(Player& player, const Encounter& monster) override;
};
