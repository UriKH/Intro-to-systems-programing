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
    string getDescription() const override;
    int playCard(Job& player) const override;

    int getLoot() const;
    int getPower() const;
    int getDamage() const;
    virtual std::string getName() const override;

    Encounter(const string name, const int power, const int loot, const int damage, const int size) :
        m_name(name), m_power(power), m_loot(loot), m_damage(damage), m_size(size){}
};
