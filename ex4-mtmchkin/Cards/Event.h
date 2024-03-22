#pragma once
#include "Card.h"

using std::string;

class Event : public Card {
private:
    string m_name;
    

public:
    string getDescription() const override;
    void playCard(const Player& player) const override;
};