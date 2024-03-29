#pragma once

// TODO

/**
 * Representation of the 
*/
class HealthPoints{
    int m_hp;
    int m_maxHP;

    static const int DEFUALT_MAX_HP = 100;

    friend bool operator<(const HealthPoints&, const HealthPoints&);
    friend bool operator==(const HealthPoints&, const HealthPoints&);
public:
    static const int MIN_HP = 0;

    explicit HealthPoints(int maxHP = DEFUALT_MAX_HP);

    bool isAlive() const;
    bool healthMaxed() const;

    HealthPoints& operator+=(const int);
    HealthPoints& operator-=(const int);
    operator int() const;
};

bool operator!=(const HealthPoints&, const HealthPoints&);
bool operator<=(const HealthPoints&, const HealthPoints&);
bool operator>(const HealthPoints&, const HealthPoints&);
bool operator>=(const HealthPoints&, const HealthPoints&);