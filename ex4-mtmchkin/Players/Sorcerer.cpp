#include "Sorcerer.h"
// #include "SorcererConfig.h"

Sorcerer::Sorcerer(const std::string& name, std::shared_ptr<Behavior> behavior)
    : Job(name, 100, 5, 2, 10, behavior, "Sorcerer"){
}

void Sorcerer::applySolarEclipse(){
    buff(1);
}