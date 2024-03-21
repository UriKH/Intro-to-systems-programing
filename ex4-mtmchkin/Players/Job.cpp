#include "Job.h"

int Job::getCombatForce() const{
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
        if (getCoinPile().pay(5)){
            getHealthPointsAsObject().heal(10);
        }
    }
}