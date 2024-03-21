#pragma once

#include <string>
#include "Player.h"

class Job : public Player{
protected:
    std::string m_jobTitle;
    Job(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior, const std::string& jobTitle);
public:
    virtual int calculateCombatPower() const;
    virtual void applyEncounter();
    virtual void applySolarEclipse();
    virtual void applyPotionsMerchant();
    virtual std::string getDescription() const override;
};
