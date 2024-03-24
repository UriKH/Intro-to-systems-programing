#pragma once

#include <string>
#include <map>
#include <vector>
#include "Player.h"
#include "Card.h"

class Job : public Player{
protected:
    std::string m_jobTitle;
    Job(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior, const std::string& jobTitle);
public:
    typedef void (*functionality)(Player&);
    typedef std::map<std::string, std::map<std::string, functionality>> functionalityMap;

    virtual int calculateCombatPower() const;
    virtual std::string getDescription() const override;
    virtual std::string getJobName() const;

    static void initializeMap(const std::map<std::string, functionality>&);
    static std::map<std::string, functionality> getDefaultFunctionlity();
    static void addFunctionality(const Job&, const Card&, Job::functionality);
    static functionality getFunctionality(const Job&, const Card&);
private:
    static functionalityMap& getfunctionalityMap();
};