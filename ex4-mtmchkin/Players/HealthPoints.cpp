#include "HealthPoints.h"
#include <stdexcept>

HealthPoints::HealthPoints(int maxHP): m_hp(maxHP), m_maxHP(maxHP){
    if (maxHP <= MIN_HP){
        throw std::invalid_argument("Maximum HP must be positive");
    }
}

int HealthPoints::getCurrentHP() const{
    return m_hp;
}

bool HealthPoints::isAlive() const{
    return m_hp != MIN_HP;
}

void HealthPoints::heal(int hp){
    if (hp < 0){
        throw std::invalid_argument("Can not add negative health points");
    }

    m_hp += hp;
    if (m_hp > MAX_HP){
        m_hp = MAX_HP;
    }
}

void HealthPoints::damage(int hp){
    if (hp < 0){
        throw std::invalid_argument("Can not apply negative damage");
    }

    m_hp -= hp;
    if (m_hp < MIN_HP){
        m_hp = MIN_HP;
    }
}

bool HealthPoints::healthMaxed() const{
    return m_hp == m_maxHP;
}

HealthPoints::operator int() const{
    return m_hp;
}