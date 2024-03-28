#include "Warrior.h"

Warrior::Warrior(const std::string& name, std::shared_ptr<Behavior> behavior)
    : Job(name, 100, 5, 2, 10, behavior, "Warrior"){}

int Warrior::calculateCombatPower() const{
    return getForce() + 2 * getLevel();
}