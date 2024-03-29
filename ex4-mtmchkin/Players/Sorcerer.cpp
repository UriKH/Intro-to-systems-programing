#include "Sorcerer.h"
// #include "SorcererConfig.h"

Sorcerer::Sorcerer(const std::string& name, std::shared_ptr<Behavior> behavior)
    : Job(name, 100, 1, 5, 10, behavior, "Sorcerer"){
}

int Sorcerer::applySolarEclipse(){
    buff(1);
    return 1;
}