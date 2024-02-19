#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

#include <string>

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
    
    // Constructors and destroyer
    Player(std::string name, int maxHP, int force);
    Player(std::string name, int maxHP);
    Player(std::string name);
    Player(const Player&) = default;
    ~Player() = default;

    // Class functions
    void printInfo() const;
    void levelUp();
    int getLevel() const;
    void buff(const int powerIncrease);
    void heal(const int healthIncrease);
    void damage(const int damagePoints);
    bool isKnockedOut() const;
    void addCoins(const int coinsIncrease);
    bool pay(const int price);
    int getAttackStrength() const;

};
#endif //EX2_PLAYER_H