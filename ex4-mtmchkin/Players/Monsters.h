#pragma once

#include "Encounter.h"

class Goblin : public Encounter{
private:
    static const int GOBLIN_POWER = 5;
    static const int GOBLIN_LOOT = 2;
    static const int GOBLIN_DAMAGE = 10;
public:
    Goblin() : Encounter("Goblin", GOBLIN_POWER, GOBLIN_LOOT, GOBLIN_DAMAGE, DEFAULT_SIZE){}
};

class Giant : public Encounter{
private:
    static const int GIANT_POWER = 12;
    static const int GIANT_LOOT = 5;
    static const int GIANT_DAMAGE = 25;
public:
    Giant() : Encounter("Giant", GIANT_POWER, GIANT_LOOT, GIANT_DAMAGE, DEFAULT_SIZE){}
};

class Dragon : public Encounter{
private:
    const int DRAGON_POWER = 17;
    const int DRAGON_LOOT = 100;
    const int DRAGON_DAMAGE = 9001;
public:
    Dragon() : Encounter("Dragon", DRAGON_POWER, DRAGON_LOOT, DRAGON_DAMAGE, DEFAULT_SIZE){}
};

class Gang : public Encounter{
public:
    Gang() : Encounter("Gang", 0, 0, 0, 0){}
    void pushBack(const Encounter& monster); //gets a monster (not gang!), and adds it to the vector
};
