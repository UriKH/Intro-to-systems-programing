#pragma once
#include "Card.h"

class Event : public Card {
private:
    string m_name;
    

public:
    string getDescription() const override;
    void playCard(Player player) const override;
};