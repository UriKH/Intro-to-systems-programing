#pragma once

#include "Encounter.h"

/**
 * Class representation of the goblin monster card
*/
class Goblin : public Encounter{
private:
    static const int GOBLIN_POWER = 5;
    static const int GOBLIN_LOOT = 2;
    static const int GOBLIN_DAMAGE = 10;
public:
    Goblin() : Encounter("Goblin", GOBLIN_POWER, GOBLIN_LOOT, GOBLIN_DAMAGE, DEFAULT_SIZE){}
};

/**
 * Class representation of a giant monster card
*/
class Giant : public Encounter{
private:
    static const int GIANT_POWER = 12;
    static const int GIANT_LOOT = 5;
    static const int GIANT_DAMAGE = 25;
public:
    Giant() : Encounter("Giant", GIANT_POWER, GIANT_LOOT, GIANT_DAMAGE, DEFAULT_SIZE){}
};

/**
 * Class representation of the dragon monster card
*/
class Dragon : public Encounter{
private:
    static const int DRAGON_POWER = 17;
    static const int DRAGON_LOOT = 100;
    static const int DRAGON_DAMAGE = 9001;
public:
    Dragon() : Encounter("Dragon", DRAGON_POWER, DRAGON_LOOT, DRAGON_DAMAGE, DEFAULT_SIZE){}
};

/**
 * Class representation of the gang monster card.
 * Gang will conatain the stats of a group of other monsters.
*/
class Gang : public Encounter{
public:
    Gang() : Encounter("Gang", 0, 0, 0, 0){}

    /**
     * Add a new monster to the gang
     * @param monster the new monster to add to the gang
    */
    void pushBack(const std::shared_ptr<Encounter> monster);

    string getDescription() const override;

};
