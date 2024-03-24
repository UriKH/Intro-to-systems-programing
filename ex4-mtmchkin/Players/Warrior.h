#pragma once
#include "Job.h"

class Warrior : public Job{
public:
    Warrior(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior);
    
    virtual int calculateCombatPower() const override;

    virtual std::string getJobName() const override;
};
