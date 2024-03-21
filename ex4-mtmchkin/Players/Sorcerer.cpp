#include "Sorcerer.h"


Sorcerer::Sorcerer(const std::string& name, int hp, int level, int force, int coins, Behavior* behavior)
    : Job(name, hp, level, force, coins, behavior, "Sorcerer"){}

void Sorcerer::applySolarEclipse(){
    buff(1);
}