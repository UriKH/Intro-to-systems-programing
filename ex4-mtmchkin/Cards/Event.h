#pragma once
#include "Card.h"

using std::string;

class Event : public Card {
protected:
    string m_name;
public:
    Event(const std::string&);
    string getDescription() const override;
    int playCard(const Player& player) const override;
    std::string getName() const override;
};

class SolarEclipse : public Event{
public:
    SolarEclipse() : Event("SolarEclipse"){}
};

class PotionsMerchant : public Event{
public:
    PotionsMerchant() : Event("PotionsMerchant"){}
};