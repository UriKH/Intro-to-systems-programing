#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <stdexcept>
#include "HealthPoints.h"
#include "CoinPile.h"

class Player{
    std::string m_name;
    HealthPoints m_hp;
    int m_level;
    int m_force;
    CoinPile m_coins;

    static const int MAX_NAME_SIZE = 15;
    static const int MIN_FORCE = 1;
    static const int MIN_LEVEL = 1;
    static const int MAX_LEVEL = 10;
public:
    Player(const std::string&, int, int, int, int);

    const std::string& getName() const;
    int getHealthPoints() const;
    // HealthPoints& getHealthPoints();
    int getLevel() const;
    int getForce() const;
    int getCoins() const;
    // CoinPile& getCoins();

    class NameTooLong;
};

class Player::NameTooLong : std::exception{
    const char* what() const override;
};

#endif