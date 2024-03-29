#include "HealthPoints.h"
#include <stdexcept>

using std::invalid_argument;

HealthPoints::HealthPoints(int maxHP): m_hp(maxHP), m_maxHP(maxHP){
    if (maxHP <= MIN_HP){
        throw invalid_argument("Maximum HP must be positive");
    }
}

bool HealthPoints::healthMaxed() const{
    return m_hp == m_maxHP;
}

HealthPoints::operator int() const{
    return m_hp;
}

HealthPoints& HealthPoints::operator+=(const int hp){
    m_hp += hp;
    if (m_hp > m_maxHP){
        m_hp = m_maxHP;
    }
    else if (m_hp < MIN_HP){
        m_hp = MIN_HP;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int hp){
    *this += -hp;
    return *this;
}

bool operator==(const HealthPoints& hp, const HealthPoints& other){
    return hp.m_hp == other.m_hp;
}

bool operator!=(const HealthPoints& hp, const HealthPoints& other){
    return !(hp == other);
}

bool operator<(const HealthPoints& hp, const HealthPoints& other){
    return hp.m_hp < other.m_hp;
}

bool operator>(const HealthPoints& hp, const HealthPoints& other){
    return !(hp < other) && hp != other;
}

bool operator<=(const HealthPoints& hp, const HealthPoints& other){
    return !(hp > other);
}

bool operator>=(const HealthPoints& hp, const HealthPoints& other){
    return !(hp < other);
}