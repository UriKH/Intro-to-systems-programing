#pragma once

#include <string>
#include <exception>
#include "HealthPoints.h"
#include "CoinPile.h"
#include "Behavior.h"

class Player{
private:
    std::string m_name;
    HealthPoints m_hp;
    int m_level;
    int m_force;
    CoinPile m_coins;
    Behavior* m_behavior;

    static const int MAX_NAME_SIZE = 15;
    static const int MIN_FORCE = 1;
    static const int MIN_LEVEL = 1;
    static const int MAX_LEVEL = 10;
public:
    Player(const std::string& name, int maxHP, int level, int force, int coins, Behavior* behavior);

    virtual std::string getName() const;
    virtual const HealthPoints& getHealthPoints() const;
    virtual HealthPoints& getHealthPoints();
    virtual const CoinPile& getCoins() const;
    virtual CoinPile& getCoins();
    virtual const Behavior& getBehavior() const;
    virtual Behavior& getBehavior();
    virtual int getLevel() const;
    virtual int getForce() const;

    virtual std::string getDescription() const;

    virtual void buff(int);
    virtual void debuff(int);
    virtual void levelUp();
};