#pragma once

#include "Encounter.h"

class Dragon : public Encounter{
private:
    const int DRAGON_POWER = 17;
    const int DRAGON_LOOT = 100;
    const int DRAGON_DAMAGE = 9001;
public: 
    Dragon() : Encounter("Dragon", DRAGON_POWER, DRAGON_LOOT, DRAGON_DAMAGE, DEFAULT_SIZE) {}
};