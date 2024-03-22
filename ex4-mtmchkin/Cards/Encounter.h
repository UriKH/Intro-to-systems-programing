#pragma once

#include "Card.h"

using std::string;

class Encounter : public Card{
private:
    string m_name;
    int m_size;
    int m_power;
    int m_loot;
    int m_damage;

public:
    string getDescription() const override;
    void playCard(const Player& player) const override;
};
