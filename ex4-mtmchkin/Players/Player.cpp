#include "Player.h"

Player::Player(const std::string& name, int hp, int level, int force, int coins)
    : m_name(name), m_hp(HealthPoints(hp)), m_level(level), m_force(force), m_coins(CoinPile(coins)){
    if (name.size() > MAX_NAME_SIZE){
        throw NameTooLong();
    }

    if (m_level > MAX_LEVEL || m_level < MIN_LEVEL){
        m_level = MIN_LEVEL;
    }

    if (m_force < MIN_FORCE){
        m_force = MIN_FORCE;
    }
}

const std::string& Player::getName() const{
    return m_name;
}

int Player::getHealthPoints() const{
    return m_hp.getCurrentHP();
}

int Player::getLevel() const{
    return m_level;
}

int Player::getForce() const {
    return m_force;
}

int Player::getCoins() const{
    return m_coins.getCoins();
}

const char* Player::NameTooLong::what() const {
    return "Name of player is too long";
}