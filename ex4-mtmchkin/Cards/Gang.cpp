#include "Monsters.h"
#include <sstream>

void Gang::pushBack(const std::shared_ptr<Encounter> monster){
    m_size++;
    m_loot += monster->getLoot();
    m_power += monster->getPower();
    m_damage += monster->getDamage();
}

string Gang::getDescription() const{
    std::stringstream description;
    description << m_name << " of " << m_size << " members (power " << m_power << ", loot " << m_loot << ", damage " << m_damage << ")";
    return description.str();
}