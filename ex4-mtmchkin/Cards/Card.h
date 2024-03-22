#pragma once

#include "../Players/Player.h"
#include <string>

class Card {
public:


    /**
     * Gets the description of the card
     * 
     * @return - the description of the card
    */
    virtual std::string getDescription() const;
    
    /**
     * Play the card for "player"
     * 
    */
    virtual void playCard(const Player& player) const;
};
