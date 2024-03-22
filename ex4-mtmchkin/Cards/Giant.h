#pragma once

#include "Encounter.h"

class Giant : public Encounter{
private:    
    const int GIANT_POWER = 12;
    const int GIANT_LOOT = 5;
    const int GIANT_DAMAGE = 25;
public: 
    Giant() : Encounter("Giant", GIANT_POWER, GIANT_LOOT, GIANT_DAMAGE, DEFAULT_SIZE){}
};