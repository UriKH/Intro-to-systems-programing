#include "Behavior.h"
#include "Player.h"

Behavior::Behavior(const std::string& name) : m_name(name){}

std::string Behavior::getName() const{
    return m_name;
}


Responsible::Responsible() : Behavior("Responsible"){}

bool Responsible::buyPotion(const Player& player) const{
    return !player.getHealthPoints().healthMaxed();
}

RiskTaking::RiskTaking() : Behavior("RiskTaking"){}

bool RiskTaking::buyPotion(const Player& player) const{
    return player.getHealthPoints() < 50;
}