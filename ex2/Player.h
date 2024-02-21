#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

#include <string>

/**
 * Representation of a player
*/
class Player{
private:
    // class fields
    std::string m_name;
    int m_level;
    int m_maxHP;
    int m_force;
    int m_HP;
    int m_coins;

    // static values
    static const int MAX_LEVEL = 10;
    static const int MIN_HP = 0;
    static const int MIN_COINS = 0;
    static const int DEFAULT_LEVEL = 1;
    static const int DEFAULT_FORCE = 5;
    static const int DEFAULT_MAX_HP = 100;

public:
    
    /**
     * Constructor for Player
     * @param name: name of the player
     * @param maxHP: optional - maximum HP of the player
     * @param foce: optional - starting force of the player
    */
    Player(std::string name, int maxHP = DEFAULT_MAX_HP, int force = DEFAULT_FORCE);
    
    /**
     * Printing info of the palyer
    */
    void printInfo() const;

    /**
     * Level up the player
    */
    void levelUp();

    /**
     * Get the current player level
     * @returns level of the player
    */
    int getLevel() const;

    /**
     * Increase force of the player by given amount
     * @param powerIncrease: amount of force to buff the player with
    */
    void buff(const int powerIncrease);

    /**
     * Heal the player by some HP amount
     * @param healthIncrease: amount of hp to add to the player
    */
    void heal(const int healthIncrease);

    /**
     * Remove HP amount from player HP
     * @param damagePoints: HP points to remove from the player
    */
    void damage(const int damagePoints);

    /**
     * Check if the player is knocked-out
     * @return true if the player is knocked-out else false 
    */
    bool isKnockedOut() const;

    /**
     * Give the player an amount of coins
     * @param coinsIncrease: amount of coins to give to the player
    */
    void addCoins(const int coinsIncrease);

    /**
     * Make the player pay a given amount of coins
     * @param price: the given price to ask the palyer to pay
     * @return true if player paid the price. false otherwise.
    */
    bool pay(const int price);

    /**
     * Get the attak strength of the player
     * @return the attak strngth of the player
    */
    int getAttackStrength() const;
};

#endif //EX2_PLAYER_H