#pragma once

#include <string>

class Player;

class Behavior{
protected:
    std::string m_name;
public:
    Behavior(const std::string& name);
    virtual bool buyPotion(const Player&) const = 0;
    virtual std::string getName() const;
};

class Responsible : public Behavior{
public:
    Responsible(const std::string& name = "Responsible");
    virtual bool buyPotion(const Player&) const override;
};

class RiskTaking : public Behavior{
public:
    RiskTaking(const std::string& name = "RiskTaking");
    virtual bool buyPotion(const Player&) const override;
};
