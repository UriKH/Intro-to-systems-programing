#include "Player.h"
#include "utilities.h"
#include <iostream>
#include <string>

Player::Player(std::string name, int maxHP, int force) : m_name(name){
    m_force = (force >= 0) ? force : DEFAULT_FORCE;
    m_level = DEFAULT_LEVEL;
    m_maxHP = (maxHP > 0) ? maxHP : DEFAULT_MAX_HP;
    m_HP = m_maxHP;
    m_coins = MIN_COINS;
}

Player::Player(std::string name, int maxHP) : m_name(name){
    m_force = DEFAULT_FORCE;
    m_level = DEFAULT_LEVEL;
    m_maxHP = (maxHP > 0) ? maxHP : DEFAULT_MAX_HP;
    m_HP = m_maxHP;
    m_coins = MIN_COINS;
}

Player::Player(std::string name) : m_name(name){
    m_force = DEFAULT_FORCE;
    m_level = DEFAULT_LEVEL;
    m_maxHP = DEFAULT_MAX_HP;
    m_HP = m_maxHP;
    m_coins = MIN_COINS;
}

void Player::printInfo() const{
    printPlayerInfo(m_name.c_str(), m_level, m_force, m_HP, m_coins);
}

void Player::levelUp(){
    if (m_level < MAX_LEVEL){
        m_level++;
    }
}

int Player::getLevel() const{
    return m_level;
}

void Player::buff(const int powerIncrease){
    if (powerIncrease > 0){
        m_force += powerIncrease;
    }
}

void Player::heal(const int healthIncrease){
    if(healthIncrease > MIN_HP){
        if((m_HP += healthIncrease) > m_maxHP){
            m_HP = m_maxHP;
        }
    }
}

void Player::damage(const int damagePoints){
    if(damagePoints > 0){
        if((m_HP -= damagePoints) < MIN_HP){
            m_HP = MIN_HP;
        }
    }
}

bool Player::isKnockedOut() const{
    return (m_HP == MIN_HP);
}

void Player::addCoins(const int coinsIncrease){
    if(coinsIncrease > MIN_COINS){
        m_coins += coinsIncrease;
    }
}

bool Player::pay(const int price){
    if(price <= m_coins && price >= 0){
        m_coins -= price;
        return true;
    }
    return false;
}

int Player::getAttackStrength() const{
    return m_force + m_level;
}
