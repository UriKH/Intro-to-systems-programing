#pragma once

#include "Encounter.h"

class Giant : public Encounter{
private:    
    static const int GIANT_POWER = 12;
    static const int GIANT_LOOT = 5;
    static const int GIANT_DAMAGE = 25;
public: 
    Giant() : Encounter("Giant", GIANT_POWER, GIANT_LOOT, GIANT_DAMAGE, DEFAULT_SIZE){}
};