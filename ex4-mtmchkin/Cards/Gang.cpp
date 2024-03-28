#include "Monsters.h"

void Gang::pushBack(const std::shared_ptr<Encounter> monster){
    m_size++;
    m_loot += monster->getLoot();
    m_power += monster->getPower();
    m_damage += monster->getDamage();
}