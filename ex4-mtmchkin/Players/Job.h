#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>
#include "Player.h"
#include "Card.h"

class Job : public Player{
protected:
    std::string m_jobTitle;
    Job(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior, const std::string& jobTitle);
public:
    typedef int (*functionality)(Player&);
    typedef std::map<std::string, std::map<std::string, functionality>> functionalityMap;

    virtual int calculateCombatPower() const;
    virtual std::string getDescription() const override;
    virtual std::string getJobName() const;

    static functionality getFunctionality(const Job&, const Card&);
    static void addFunctionality(const std::string&, const Card&, Job::functionality);
    static void addFunctionality(const std::string&, std::vector<std::pair<Card&, Job::functionality>>);
    static void initializeMap(const std::map<std::string, functionality>&);
    static std::map<std::string, functionality> getDefaultFunctionlity();
private:
    static functionalityMap& getfunctionalityMap();
};