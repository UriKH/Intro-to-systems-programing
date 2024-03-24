#include "Sorcerer.h"
#include "Event.h"

Sorcerer::Sorcerer(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior)
    : Job(name, hp, level, force, coins, behavior, "Sorcerer"){
}

std::string Sorcerer::getJobName() const{
    return "Sorcerer";
}