#include "Job.h"
#include "Player.h"
#include "../Cards/Encounter.h"
#include <sstream>

using std::shared_ptr;
using std::string;

Job::Job(const string& jobTitle) : m_jobTitle(jobTitle){}

int Job::calculateCombatPower(Player& player) const{
    return player.getForce() + player.getLevel();
}

int Job::applyEncounter(Player& player, const Encounter& monster){
    if (calculateCombatPower(player) <= monster.getPower()){
        player.getHealthPoints() -= monster.getDamage();
        return -monster.getDamage();
    }
    player.getCoins() += monster.getLoot();
    player.levelUp(1);
    return monster.getLoot();
}

int Job::applySolarEclipse(Player& player){
    return player.debuff(1);
}

int Job::applyPotionsMerchant(Player& player){
    int counter = 0;
    while (player.getBehavior().buyPotion(player)){
        if (player.getCoins() >= 5){
            player.getCoins() -= 5;
            player.getHealthPoints() += 10;
            counter++;
        }
        else{
            break;
        }
    }
    return counter;
}

std::string Job::getName() const{
    return m_jobTitle;
}