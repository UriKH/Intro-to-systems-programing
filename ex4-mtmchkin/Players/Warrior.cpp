#include "Warrior.h"

Warrior::Warrior(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior)
    : Job(name, hp, level, force, coins, behavior, "Warrior"){}

int Warrior::calculateCombatPower() const{
    return getForce() + 2 * getLevel();
}