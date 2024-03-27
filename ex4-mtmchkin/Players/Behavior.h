#pragma once

#include <string>

class Player;

//TODO

class Behavior{
protected:
    std::string m_name;
public:
    explicit Behavior(const std::string& name);
    virtual std::string getName() const;

    virtual bool buyPotion(const Player&) const = 0;
};

class Responsible : public Behavior{
public:
    explicit Responsible();
    virtual bool buyPotion(const Player&) const override;
};

class RiskTaking : public Behavior{
public:
    explicit RiskTaking();
    virtual bool buyPotion(const Player&) const override;
};
