#include "HealthPoints.h"
#include <stdexcept>

HealthPoints::HealthPoints(int maxHP = MAX_HP): m_hp(maxHP), m_maxHP(maxHP){
    if (maxHP > MAX_HP || maxHP < MIN_HP){
        throw InvalidArgument();
    }
}

int HealthPoints::getCurrentHP() const{
    return m_hp;
}

bool HealthPoints::isDead() const {
    return m_hp == MIN_HP;
}

void HealthPoints::heal(int hp){
    if (hp < 0){
        throw InvalidArgument();
    }

    m_hp += hp;
    if (m_hp > MAX_HP){
        m_hp = MAX_HP;
    }
}

void HealthPoints::damage(int hp){
    if (hp < 0){
        throw InvalidArgument();
    }

    m_hp -= hp;
    if (m_hp < MIN_HP){
        m_hp = MIN_HP;
    }
}