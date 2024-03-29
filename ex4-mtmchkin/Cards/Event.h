#pragma once
#include "Card.h"

using std::string;

// TODO

class Event : public Card{
protected:
    string m_name;
public:
    Event(const std::string&);

    string getDescription() const override;
    std::string getName() const override;
};

class SolarEclipse : public Event{
public:
    SolarEclipse() : Event("SolarEclipse"){}

    int playCard(Job& player) const override{
        return player.applySolarEclipse();
    }
};

class PotionsMerchant : public Event{
public:
    PotionsMerchant() : Event("PotionsMerchant"){}

    int playCard(Job& player) const override{
        return player.applyPotionsMerchant();
    }
};