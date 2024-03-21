#include "Player.h"

#include <string>
#include <stdexcept>

Player::Player(const std::string& name, int hp, int level, int force, int coins, Behavior* behavior)
    : m_name(name), m_hp(HealthPoints(hp)), m_level(level), m_force(force), m_coins(CoinPile(coins)), m_behavior(behavior){
    if (m_behavior == nullptr){
        throw std::invalid_argument("behavior must not be nullptr");
    }

    if (name.size() > MAX_NAME_SIZE){
        throw std::invalid_argument("Name is longer than " + std::to_string(MAX_NAME_SIZE) + "characters");
    }

    if (m_level > MAX_LEVEL || m_level < MIN_LEVEL){
        m_level = MIN_LEVEL;
    }

    if (m_force < MIN_FORCE){
        m_force = MIN_FORCE;
    }
}

std::string Player::getName() const{
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

Behavior& Player::getBehavior(){
    return *m_behavior;
}

CoinPile& Player::getCoinPile(){
    return m_coins;
}

void Player::buff(int buff){
    if (buff < 0){
        throw std::invalid_argument("buff gets only positive values");
    }
    m_force += buff;
}

void Player::debuff(int debuff){
    if (debuff < 0){
        throw std::invalid_argument("debuff gets only positive values");
    }

    m_force -= debuff;
    if (m_force < MIN_FORCE){
        m_force = MIN_FORCE;
    }
}

void Player::levelUp(){
    m_level += 1;
}

HealthPoints& Player::getHealthPointsAsObject(){
    return m_hp;
}

const HealthPoints& Player::getHealthPointsAsObject() const{
    return m_hp;
}

std::string Player::getDescription() const{
    return m_name + ", Unemployed with" + m_behavior->getName() + " behavior (level " + std::to_string(m_level) + ", force " + std::to_string(m_force) + ")";
}