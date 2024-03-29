#include "Encounter.h"
#include <sstream>

std::string Encounter::getDescription() const{
    std::stringstream description;
    description << m_name << " (power " << m_power << ", loot " << m_loot << ", damage " << m_damage << ")";
    return description.str();
}

int Encounter::playCard(Player& player) const{
    return player.getJob().applyEncounter(player, *this);
}

int Encounter::getLoot() const{
    return m_loot;
}

int Encounter::getPower() const{
    return m_power;
}

int Encounter::getDamage() const{
    return m_damage;
}

std::string Encounter::getName() const{
    return m_name;
}
