#include "Job.h"

using std::shared_ptr;
using std::string;
using std::to_string;

Job::Job(const std::string& name, int hp, int level, int force, int coins, shared_ptr<Behavior> behavior, const string& jobTitle)
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

string Job::getDescription() const {
    return getName() + ", Unemployed with" + getBehavior().getName() + " behavior (level " + to_string(getLevel()) + ", force " + to_string(getForce()) + ")";
}