#pragma once

#include "Encounter.h"

class Goblin : public Encounter{
private:
    const int GOBLIN_POWER = 5;
    const int GOBLIN_LOOT = 2;
    const int GOBLIN_DAMAGE = 10;
public: 
    Goblin() : Encounter("Goblin", GOBLIN_POWER, GOBLIN_LOOT, GOBLIN_DAMAGE, DEFAULT_SIZE){}
};