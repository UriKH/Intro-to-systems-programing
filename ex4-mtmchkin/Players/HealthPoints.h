#pragma once

// TODO

/**
 * Representation of the 
*/
class HealthPoints{
    int m_hp;
    int m_maxHP;

    static const int MAX_HP = 100;
    static const int MIN_HP = 0;
public:
    explicit HealthPoints(int maxHP = MAX_HP);

    int getCurrentHP() const;
    bool isAlive() const;
    void heal(int hp);
    void damage(int hp);
    bool healthMaxed() const;

    operator int() const;
};
