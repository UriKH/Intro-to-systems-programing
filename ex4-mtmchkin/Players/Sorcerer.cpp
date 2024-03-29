#include "Sorcerer.h"
// #include "SorcererConfig.h"

Sorcerer::Sorcerer()
    : Job("Sorcerer"){
}

int Sorcerer::applySolarEclipse(Player& player){
    player.buff(1);
    return 1;
}