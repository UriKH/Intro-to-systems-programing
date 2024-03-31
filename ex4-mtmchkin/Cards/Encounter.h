#pragma once

#include "Card.h"

using std::string;

// TODO

class Encounter : public Card{
protected:
    static const int DEFAULT_SIZE = 1;

    string m_name;
    int m_power;
    int m_loot;
    int m_damage;
    int m_size = DEFAULT_SIZE;

public:
    /**
     * Get the description of the card
     * 
     * @return the card's description
    */
    string getDescription() const override;

    /**
     * Plays the encounter card for the given player
     * 
     * @param player the player that plays the encounter
     * 
     * @return if lost the encounter - the damage, if won - the loot
    */
    int playCard(Player& player) const override;

    /**
     * Get the loot of the card
     * 
     * @return the card's loot
    */
    int getLoot() const;

    /**
     * Get the power of the card
     * 
     * @return the card's power
    */
    int getPower() const;

    /**
     * Get the damage of the card
     * 
     * @return the card's damage
    */
    int getDamage() const;

    /**
     * Get the name of the card
     * 
     * @return the card's name
    */
    virtual std::string getName() const override;

    Encounter(const string name, const int power, const int loot, const int damage, const int size) :
        m_name(name), m_power(power), m_loot(loot), m_damage(damage), m_size(size){}
};
