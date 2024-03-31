#include "Sorcerer.h"
#include <iostream>
using namespace std;

Sorcerer::Sorcerer()
    : Job("Sorcerer"){
}

int Sorcerer::applySolarEclipse(Player& player){
    player.buff(1);
    return 1; 
}