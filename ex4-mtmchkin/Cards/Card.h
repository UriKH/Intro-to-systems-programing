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
    virtual std::string getDescription() const = 0;
    
    /**
     * Play the card for "player"
     * 
    */
    virtual int playCard(const Player& player) const = 0;

    virtual std::string getName() const = 0;
};

