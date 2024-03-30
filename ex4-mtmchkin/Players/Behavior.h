#pragma once

#include <string>

class Player;

class Behavior{
protected:
    std::string m_name;
public:
    /**
     * Create beavior with a name
     *
     * @param name the name of the behavior
    */
    explicit Behavior(const std::string& name);

    /**
     * gets the name of the behavior
    */
    virtual std::string getName() const;

    /**
     * decide if to buy a potion or not
    */
    virtual bool buyPotion(const Player&) const = 0;
};

class Responsible : public Behavior{
public:
    /**
     * Create a responsible behavior
    */
    explicit Responsible();

    /**
     * decide if to buy a potion or not
    */
    virtual bool buyPotion(const Player&) const override;
};

class RiskTaking : public Behavior{
public:
    /**
     * Create a risk-taking behavior
    */
    explicit RiskTaking();

    /**
     * decide if to buy a potion or not
    */
    virtual bool buyPotion(const Player&) const override;
};
