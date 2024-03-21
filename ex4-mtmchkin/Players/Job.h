#pragma once

#include <string>
#include "Player.h"

class Job : public Player{
    Job() = default;
public:
    virtual int getCombatForce() const;
    virtual void applyEncounter();
    virtual void applySolarEclipse();
    virtual void applyPotionsMerchant();
};
