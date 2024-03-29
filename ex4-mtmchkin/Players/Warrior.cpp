#include "Warrior.h"
#include "../Cards/Encounter.h"
#include <iostream>

Warrior::Warrior() : Job("Warrior"){}

int Warrior::calculateCombatPower(Player& player) const{
    return 2 * player.getForce() + player.getLevel();
}

int Warrior::applyEncounter(Player& player, const Encounter& monster){
    if (calculateCombatPower(player) <= monster.getPower()){
        player.getHealthPoints() -= monster.getDamage();
        return -monster.getDamage();
    }
    player.getCoins() += monster.getLoot();
    player.levelUp(1);
    return monster.getLoot();
}