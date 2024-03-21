#pragma once
#include "Job.h"

class Sorcerer : public Job{
public:
    Sorcerer(const std::string& name, int hp, int level, int force, int coins, Behavior* behavior);

    virtual void applySolarEclipse() override;
};