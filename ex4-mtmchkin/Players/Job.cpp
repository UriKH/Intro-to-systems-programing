#include "Job.h"
#include "../Cards/Card.h"
#include <sstream>
#include <stdexcept>

using std::shared_ptr;
using std::string;
using std::map;

#define JOB_NAME "Job"

Job::Job(const string& name, int hp, int level, int force, int coins, shared_ptr<Behavior> behavior, const string& jobTitle)
    : Player(name, hp, level, force, coins, behavior), m_jobTitle(jobTitle){
}

int Job::calculateCombatPower() const{
    return getForce() + getLevel();
}

string Job::getDescription() const{
    std::stringstream ss;
    ss << getName() << ", " << m_jobTitle << " with" << getBehavior().getName() << " behavior (level " << getLevel() << ", force " << getForce() << ")";
    return ss.str();
}

void Job::initializeMap(CardPlayerActionMap functions){
    static bool called = false;

    if (called){
        throw Job::InvalidInitialization();
    }

    CardPlayerActionMap& funcMap = getfunctionalityMap();
    funcMap = functions;
    called = true;
}

Job::CardPlayerActionMap& Job::getfunctionalityMap(){
    static Job::CardPlayerActionMap funcMap;

    // prevents infinite re-calling from initializeMsp
    static bool called = false;

    if (funcMap.size() == 0 && !called){
        called = true;
        initializeMap(getDefaultActions());
    }
    return funcMap;
}

Job::PlayerAction Job::getPlayerAction(const Job& job, const Card& card){    
    auto& cardFunctions = getfunctionalityMap()[card.getName()];

    if (cardFunctions.find(job.getJobName()) != cardFunctions.end()){
        return cardFunctions[job.getJobName()];
    }
    else if (cardFunctions.find(JOB_NAME) != cardFunctions.end()){
        return cardFunctions[JOB_NAME];
    }

    throw ActionNotFound(card.getName(), job.getJobName());
}

int defaultApplyEncounter(Player& p, const Card* card){
    // TODO: some fight function
    return 0;
}

int defaultApplySolarEclipse(Player& p, const Card* card = nullptr){
    p.debuff(1);
    return -1;
}

int defaultApplyPotionsMerchant(Player& p, const Card* card = nullptr){
    int counter = 0;
    while (p.getBehavior().buyPotion(p)){
        if (p.getCoins().pay(5)){
            p.getHealthPoints().heal(10);
            counter++;
        }
    }
    return counter;
}

Job::CardPlayerActionMap Job::getDefaultActions(){
    Job::CardPlayerActionMap defaultFunctionlity;
    defaultFunctionlity["Giant"][JOB_NAME] = defaultApplyEncounter;
    defaultFunctionlity["Goblin"][JOB_NAME] = defaultApplyEncounter;
    defaultFunctionlity["Gang"][JOB_NAME] = defaultApplyEncounter;
    defaultFunctionlity["SolarEclipse"][JOB_NAME] = defaultApplySolarEclipse;
    defaultFunctionlity["PotionsMerchant"][JOB_NAME] = defaultApplyPotionsMerchant;
    return defaultFunctionlity;
}

Job::ActionNotFound::ActionNotFound(const std::string& cardName, const std::string& jobName){
    m_message = "No implementation of card \'" + cardName + "\' found for job \'" + jobName
        + "\' nor default implementation found";
}

const char* Job::ActionNotFound::what() const noexcept{
    return m_message.c_str();
}

const char* Job::InvalidInitialization::what() const noexcept{
    return "Cannot reset actions after first initialization";
}