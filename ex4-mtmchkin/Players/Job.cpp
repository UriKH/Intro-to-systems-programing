#include "Job.h"
#include "Event.h"
#include "Encounter.h"
#include "Giant.h"
#include "Gang.h"
#include "Goblin.h"
#include <sstream>
#include <stdexcept>

using std::shared_ptr;
using std::string;
using std::map;

#define JOB_NAME "Job"

Job::Job(const string& name, int hp, int level, int force, int coins, shared_ptr<Behavior> behavior, const string& jobTitle)
    : Player(name, hp, level, force, coins, behavior), m_jobTitle(jobTitle){
    initializeMap(getDefaultFunctionlity());
}

std::string Job::getJobName() const{
    return JOB_NAME;
}

void Job::initializeMap(const std::map<std::string, functionality>& functions){
    functionalityMap& funcMap = getfunctionalityMap();
    if (funcMap.size() > 0){
        return;
    }
    
    for (auto it = functions.begin(); it != functions.end(); ++it){
        funcMap[it->first][JOB_NAME] = it->second;
    }
}

int Job::calculateCombatPower() const{
    return getForce() + getLevel();
}

string Job::getDescription() const{
    std::stringstream ss;
    ss << getName() << ", " << m_jobTitle << " with" << getBehavior().getName() << " behavior (level " << getLevel() << ", force " << getForce() << ")";
    return ss.str();
}

Job::functionalityMap& Job::getfunctionalityMap(){
    static Job::functionalityMap funcMap;
    return funcMap;
}

void Job::addFunctionality(const Job& job, const Card& card, Job::functionality applyFunction){
    if (job.getJobName() == JOB_NAME){
        throw std::logic_error("Cannot change default function calles after initialization");
    }

    if (getfunctionalityMap().find(card.getName()) == getfunctionalityMap().end()){
        throw std::invalid_argument("Card of type \'" + card.getName() + "\' is not recognized in game");
    }

    getfunctionalityMap()[card.getName()][job.getJobName()] = applyFunction;
}

Job::functionality Job::getFunctionality(const Job& job, const Card& card){    
    auto& cardFunctions = getfunctionalityMap()[card.getName()];
    auto it = cardFunctions.find(job.getJobName());

    if (it != cardFunctions.end()){
        return cardFunctions[job.getJobName()];
    }
    else if (cardFunctions[JOB_NAME] != nullptr){
        return cardFunctions[JOB_NAME];
    }

    throw std::invalid_argument("No implementation of card \'" + card.getName()
        + "\' found for default and job \'" + job.getJobName() + "\'");
}

void DefaultApplyEncounter(Player& p){
    // TODO: some fight function
}

void DefaultApplySolarEclipse(Player& p){
    p.debuff(1);
}

void DefaultApplyPotionsMerchant(Player& p){
    while (p.getBehavior().buyPotion(p)){
        if (p.getCoins().pay(5)){
            p.getHealthPoints().heal(10);
        }
    }
}

std::map<std::string, Job::functionality> Job::getDefaultFunctionlity(){
    std::map<std::string, Job::functionality> defaultFunctionlity;
    defaultFunctionlity[Giant().getName()] = DefaultApplyEncounter;
    defaultFunctionlity[Goblin().getName()] = DefaultApplyEncounter;
    defaultFunctionlity[Gang().getName()] = DefaultApplyEncounter;
    defaultFunctionlity[SolarEclipse().getName()] = DefaultApplySolarEclipse;
    defaultFunctionlity[PotionsMerchant().getName()] = DefaultApplyPotionsMerchant;
    return defaultFunctionlity;
}