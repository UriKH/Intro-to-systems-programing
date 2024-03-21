#include "Job.h"

Job::Job(const std::string& name, int hp, int level, int force, int coins, Behavior* behavior, const std::string& jobTitle)
    : Player(name, hp, level, force, coins, behavior), m_jobTitle(jobTitle){}

int Job::calculateCombatPower() const{
    return getForce() + getLevel();
}

void Job::applyEncounter(){
    // TODO: some fight function
}

void Job::applySolarEclipse(){
    debuff(1);
}

void Job::applyPotionsMerchant(){
    while (getBehavior().buyPotion(*this)){
        if (getCoins().pay(5)){
            getHealthPoints().heal(10);
        }
    }
}

std::string Job::getDescription() const {
    return getName() + ", Unemployed with" + getBehavior().getName() + " behavior (level " + std::to_string(getLevel()) + ", force " + std::to_string(getForce()) + ")";
}