#include "Job.h"
#include "../Cards/Encounter.h"
#include <sstream>

using std::shared_ptr;
using std::string;

Job::Job(const string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior, const string& jobTitle)
    : Player(name, hp, level, force, coins, behavior), m_jobTitle(jobTitle){}

int Job::calculateCombatPower() const{
    return getForce() + getLevel();
}

int Job::applyEncounter(const Encounter& monster){
    if (calculateCombatPower() <= monster.getPower()){
        getHealthPoints() -= monster.getDamage();
        return -monster.getDamage();
    }
    getCoins() += monster.getLoot();
    levelUp(1);
    return monster.getLoot();
}

int Job::applySolarEclipse(){
    debuff(1);
    return -1;
}

int Job::applyPotionsMerchant(){
    int counter = 0;
    while (getBehavior().buyPotion(*this)){
        if (getCoins() -= 5){
            getHealthPoints() += 10;
            counter++;
        }
        else{
            break;
        }
    }
    return counter;
}

string Job::getDescription() const{
    std::stringstream ss;
    ss << getName() << ", " << m_jobTitle << " with " << getBehavior().getName() << " behavior (level " << getLevel() << ", force " << getForce() << ")";
    return ss.str();
}