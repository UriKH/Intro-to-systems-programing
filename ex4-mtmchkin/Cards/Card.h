#pragma once

#include "../Players/Player.h"
#include <string>

using std::string; 

class Card {
public:


    /**
     * Gets the description of the card
     * 
     * @return - the description of the card
    */
    virtual string getDescription() const;
    
    /**
     * Play the card for "player"
     * 
    */
    virtual void playCard(Player player) const;
};
