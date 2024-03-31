#pragma once
#include "Card.h"

using std::string;

// TODO

class Event : public Card{
protected:
    string m_name;
public:
    Event(const std::string&);

    /**
     * Get the description of the card
     * 
     * @return the card's description
    */
    string getDescription() const override;

    /**
     * Get the name of the card
     * 
     * @return the card's name
    */
    std::string getName() const override;
};

class SolarEclipse : public Event{
public:
    SolarEclipse() : Event("SolarEclipse"){}

    /**
     * Plays the solar eclipse card for the given player
     * 
     * @param player the player that plays the card
     * 
     * @return the change in the player's force
    */
    int playCard(Player& player) const override{
        return player.getJob().applySolarEclipse(player);
    }
};

class PotionsMerchant : public Event{
public:
    PotionsMerchant() : Event("PotionsMerchant"){}

    /**
     * Plays the Potions Merchant card for the give player
     * 
     * @param player the player that plays the card
     * 
     * @return the amount of potions bought
    */
    int playCard(Player& player) const override{
        return player.getJob().applyPotionsMerchant(player);
    }
};