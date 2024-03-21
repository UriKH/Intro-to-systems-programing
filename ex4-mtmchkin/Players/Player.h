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

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    virtual std::string getName() const;

    /**
    * Gets the amount of health points the player currently has
    *
    * @return - health points of the player
   */
    virtual int getHealthPoints() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    virtual int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    virtual int getForce() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    virtual int getCoins() const;

    virtual CoinPile& getCoinPile();

    virtual Behavior& getBehavior();

    virtual void buff(int);

    virtual void debuff(int);

    virtual void levelUp();

    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    virtual std::string getDescription() const;

    virtual HealthPoints& getHealthPointsAsObject();
    virtual const HealthPoints& getHealthPointsAsObject() const;
};