#include "Sorcerer.h"
#include "Event.h"

void applySolarEclipse(Player& p){
    p.buff(1);
}

Sorcerer::Sorcerer(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior)
    : Job(name, hp, level, force, coins, behavior, "Sorcerer"){
    Job::addFunctionality(*this, SolarEclipse(), applySolarEclipse);
}


std::string Sorcerer::getJobName() const{
    return "Sorcerer";
}