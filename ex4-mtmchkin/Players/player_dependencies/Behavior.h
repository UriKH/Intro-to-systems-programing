#pragma once

#include "../Player.h"

class Behavior{
public:
    virtual bool buyPotion(const Player&) = 0;
};

class Responsible : public Behavior{
public:
    virtual bool buyPotion(const Player&) override;
};

class RiskTaking : public Behavior{
public:
    virtual bool buyPotion(const Player&) override;
};