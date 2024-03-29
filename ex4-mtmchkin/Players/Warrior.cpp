#include "Warrior.h"
#include "../Cards/Encounter.h"
#include <iostream>

Warrior::Warrior(const std::string& name, std::shared_ptr<Behavior> behavior)
    : Job(name, 100, 1, 5, 10, behavior, "Warrior"){}

int Warrior::calculateCombatPower() const{
    return 2 * getForce() + getLevel();
}

int Warrior::applyEncounter(const Encounter& monster){
    if (calculateCombatPower() <= monster.getPower()){
        getHealthPoints() -= monster.getDamage();
        return -monster.getDamage();
    }
    getCoins() += monster.getLoot();
    levelUp(1);
    return monster.getLoot();
}