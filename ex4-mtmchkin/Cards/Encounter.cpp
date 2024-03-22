#include "Encounter.h"

string Encounter::getDescription() const{
    return string();
}

void Encounter::playCard(const Player& player) const{
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
