#include "Behavior.h"
#include "Player.h"


Behavior::Behavior(const std::string& name) : m_name(name){}

std::string Behavior::getName() const{
    return m_name;
}


Responsible::Responsible(const std::string& name) : Behavior(name){}

bool Responsible::buyPotion(const Player& player) const{
    return !player.getHealthPointsAsObject().healthMaxed();
}


RiskTaking::RiskTaking(const std::string& name) : Behavior(name){}

bool RiskTaking::buyPotion(const Player& player) const{
    return player.getHealthPoints() < 50;
}