#pragma once

#include "Card.h"

class Encounter : public Card{
private:
    string m_name;
    int m_size;
    int m_power;
    int m_loot;
    int m_damage;

    int calculateSize() const;
    int calculatePower() const;
    int calculateLoot() const;
    int calculateDamage() const;

public:
    string getDescription() const override;
    void playCard(Player player) const override;
};
