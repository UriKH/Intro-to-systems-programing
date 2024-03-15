#include "HealthPoints.h"

HealthPoints::HealthPoints(const int points) : m_currentHP(points), m_maxHP(points){
    if (points <= 0){
        throw InvalidArgument();
    }
}

HealthPoints& HealthPoints::operator+=(const int hp){
    m_currentHP += hp;
    if (m_currentHP > m_maxHP){
        m_currentHP = m_maxHP;
    }
    else if (m_currentHP < 0){
        m_currentHP = 0;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int hp){
    *this += -hp;
    return *this;
}

HealthPoints HealthPoints::operator+(const int addend) const{
    HealthPoints result = HealthPoints(m_maxHP);
    result.m_currentHP = m_currentHP;
    result += addend;
    return result;
}

HealthPoints operator+(const int addend1, const HealthPoints& addend2){
    return addend2 + addend1;
}

HealthPoints HealthPoints::operator-(const int minuend) const{
    HealthPoints result = HealthPoints(m_maxHP);
    result.m_currentHP = m_currentHP;
    result -= minuend;
    return result;
}

HealthPoints operator-(const int minuend1, const HealthPoints& minuend2){
    return minuend2 - minuend1;
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& hp){
    os << hp.m_currentHP << "(" << hp.m_maxHP << ")";
    return os;
}

bool operator==(const HealthPoints& hp, const HealthPoints& other){
    return hp.m_currentHP == other.m_currentHP;
}

bool operator!=(const HealthPoints& hp, const HealthPoints& other){
    return !(hp == other);
}

bool operator<(const HealthPoints& hp, const HealthPoints& other){
    return hp.m_currentHP < other.m_currentHP;
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
