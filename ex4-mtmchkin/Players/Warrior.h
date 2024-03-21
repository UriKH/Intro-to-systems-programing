#pragma once
#include "Job.h"

class Warrior : public Job{
public:
    Warrior(const std::string& name, int hp, int level, int force, int coins, Behavior* behavior);
    
    virtual int calculateCombatPower() const override;
};


