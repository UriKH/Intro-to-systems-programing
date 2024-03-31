#pragma once

#include <string>
#include <exception>
#include <memory>
#include "HealthPoints.h"
#include "CoinPile.h"
#include "Behavior.h"
#include "Job.h"
#include "../gameConfig.h"

class Player{
private:
    std::string m_name;
    HealthPoints m_hp;
    int m_level;
    int m_force;
    CoinPile m_coins;
    std::unique_ptr<Behavior> m_behavior = nullptr;
    std::unique_ptr<Job> m_job = nullptr;
public:
    /**
     * Constructor of Player
     *
     * @param name the name of the player
     * @param maxHp the maximum health points
     * @param level level of the player
     * @param force force of the player
     * @param coins starting coins amount
     * @param behavior the behavior type of the player
    */
    Player(const std::string& name, std::unique_ptr<Behavior> behavior, std::unique_ptr<Job> job,
        int maxHP = Configurations::Player::MAX_HP,
        int level = Configurations::Player::STARTING_LEVEL,
        int force = Configurations::Player::STARTING_FORCE,
        int coins = Configurations::Player::STARTING_COINS);

    /**
     * getter for the name of the player
     *
     * @return the player's name
    */
    virtual std::string getName() const;

    /**
     * getter for the player's health points
     *
     * @return HealthPoints represenation of the player
    */
    virtual const HealthPoints& getHealthPoints() const;

    /**
     * getter for the player's health points
     *
     * @return HealthPoints represenation of the player
    */
    virtual HealthPoints& getHealthPoints();

    /**
     * getter for the player's coins
     *
     * @return Coin pile represenation of the player's coins
    */
    virtual const CoinPile& getCoins() const;

    /**
     * getter for the player's coins
     *
     * @return Coin pile represenation of the player's coins
    */
    virtual CoinPile& getCoins();

    /**
     * getter for the player's behavior type
     *
     * @return the player's behavior
    */
    virtual const Behavior& getBehavior() const;

    /**
     * getter for the player's behavior type
     *
     * @return the player's behavior
    */
    virtual Behavior& getBehavior();

    /**
     * getter for the player's level
     *
     * @return the player's behavior
    */
    virtual int getLevel() const;

    /**
     * getter for the player's force
     *
     * @return the player's force
    */
    virtual int getForce() const;

    /**
     * Gets the player's job name
    */
    virtual Job& getJob() const;

    /**
     * creates a string representaion of the player
     *
     * @return the player's string representation
    */
    virtual std::string getDescription() const;

    /**
     * check if the player has maximum level
     *
     * @return true if player is maxed out else false
    */
    virtual bool isMaxedOut() const;

    /**
     * buff player by some amount
     *
     * @param force amount of force to buff the player by
    */
    virtual void buff(int);

    /**
     * debuff player by some amount
     *
     * @param force amount of force to debuff the player by
     * @return the change in the amount of force
    */
    virtual int debuff(int);

    /**
     * Level up player by some amount
     *
     * @param levels amount of levels to level up by
    */
    virtual void levelUp(int);

    /**
     * Check if the players name is valid
     *
     * @param name The player's name
     * @return ture if name is valid else false
    */
    static bool checkName(const std::string& name);

    /**
     * Check if the player's health is full
     *
     * @return true if the player's HP is maximal else false
    */
    bool healthMaxed() const;
};