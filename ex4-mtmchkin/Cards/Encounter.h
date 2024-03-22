#pragma once

#include "Card.h"

using std::string;

class Encounter : public Card{
protected:
    static const int DEFAULT_SIZE = 1;

    string m_name;
    int m_power;
    int m_loot;
    int m_damage;
    int m_size = DEFAULT_SIZE;

public:
    string getDescription() const override;
    void playCard(const Player& player) const override;

    int getLoot() const;
    int getPower() const;
    int getDamage() const;

    Encounter(const string name, const int power, const int loot, const int damage, const int size) :
     m_name(name), m_power(power), m_loot(loot), m_damage(damage), m_size(size){};
};
