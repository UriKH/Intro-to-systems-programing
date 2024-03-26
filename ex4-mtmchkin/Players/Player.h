#pragma once

#include <string>
#include <exception>
#include <memory>
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
    std::shared_ptr<Behavior> m_behavior = nullptr;

    static const int MAX_NAME_SIZE = 15;
    static const int MIN_FORCE = 1;
    static const int MIN_LEVEL = 1;
    static const int MAX_LEVEL = 10;
public:
    Player(const std::string& name, int maxHP, int level, int force, int coins, std::shared_ptr<Behavior> behavior);

    /**
     * getter for the name of the player
     * @return the player's name
    */
    virtual std::string getName() const;

    /**
     * getter for the player's health points
     * @return HealthPoints represenation of the player
    */
    virtual const HealthPoints& getHealthPoints() const;

    /**
     * getter for the player's health points
     * @return HealthPoints represenation of the player
    */
    virtual HealthPoints& getHealthPoints();

    /**
     * getter for the player's coins
     * @return Coin pile represenation of the player's coins
    */
    virtual const CoinPile& getCoins() const;

    /**
     * getter for the player's coins
     * @return Coin pile represenation of the player's coins
    */
    virtual CoinPile& getCoins();

    /**
     * getter for the player's behavior type
     * @return the player's behavior
    */
    virtual const Behavior& getBehavior() const;

    /**
     * getter for the player's behavior type
     * @return the player's behavior
    */
    virtual Behavior& getBehavior();

    /**
     * getter for the player's level
     * @return the player's behavior
    */
    virtual int getLevel() const;

    /**
     * getter for the player's force
     * @return the player's force
    */
    virtual int getForce() const;

    /**
     * creates a string representaion of the player
     * @return the player's string representation
    */
    virtual std::string getDescription() const;

    /**
     * check if the player has maximum level
     * @return true if player is maxed out else false
    */
    virtual bool isMaxedOut() const;
    // virtual bool isKnockedOut() const;

    /**
     * buff player by some amount
     * @param force amount of force to buff the player by
    */
    virtual void buff(int);

    /**
     * debuff player by some amount
     * @param force amount of force to debuff the player by
    */
    virtual void debuff(int);

    /**
     * Level up player by some amount
     * @param levels amount of levels to level up by
    */
    virtual void levelUp(int);
};