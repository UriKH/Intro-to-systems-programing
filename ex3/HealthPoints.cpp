#include "HealthPoints.h"

HealthPoints::HealthPoints(int hp) : m_maxHp(MAX_DEFAULT_HP){
    if (hp <= 0){
        throw HealthPoints::InvalidArgument();
    }
    m_maxHp = hp;
    m_currentHp = m_maxHp;
}

HealthPoints& HealthPoints::operator+=(const int hp){
    this->m_currentHp += hp;
    if (this->m_currentHp > this->m_maxHp){
        this->m_currentHp = this->m_maxHp;
    }
    else if (this->m_currentHp < 0){
        this->m_currentHp = 0;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int hp){
    *this += -hp;
    return *this;
}

HealthPoints HealthPoints::operator+(const int addend) const{
    HealthPoints result = HealthPoints(this->m_maxHp);
    result.m_currentHp = this->m_currentHp;
    result += addend;
    return result;
}

HealthPoints operator+(const int addend1, const HealthPoints& addend2){
    return addend2 + addend1;
}

HealthPoints HealthPoints::operator-(const int minuend) const{
    HealthPoints result = HealthPoints(this->m_maxHp);
    result.m_currentHp = this->m_currentHp;
    result -= minuend;
    return result;
}

HealthPoints operator-(const int minuend1, const HealthPoints& minuend2){
    return minuend2 - minuend1;
}

bool operator==(const HealthPoints& hp, const HealthPoints& other){
    return hp.m_currentHp == other.m_currentHp;
}

bool operator!=(HealthPoints& hp, const HealthPoints& other){
    return !(hp == other);
}

bool operator<(const HealthPoints& hp, const HealthPoints& other){
    return hp.m_currentHp < other.m_currentHp;
}

bool operator<=(const HealthPoints& hp, const HealthPoints& other){
    return hp == other || hp > other;
}

bool operator>(const HealthPoints& hp, const HealthPoints& other){
    return !(hp <= other);
}

bool operator>=(const HealthPoints& hp, const HealthPoints& other){
    return !(hp < other);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& hp){
    os << hp.m_currentHp << "(" << hp.m_maxHp << ")";
    return os;
}