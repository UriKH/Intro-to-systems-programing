#ifndef HEALTH_POINTS_H
#define HEALTH_POINTS_H

#include <iostream>

class HealthPoints{
public:
    HealthPoints(int hp = MAX_DEFAULT_HP);

    HealthPoints& operator+=(const int);
    HealthPoints& operator-=(const int);
    HealthPoints operator+(const int) const;
    HealthPoints operator-(const int) const;

    class InvalidArgument{};
private:
    int m_currentHP;
    int m_maxHP;

    static const int MAX_DEFAULT_HP = 100;

    friend bool operator<(const HealthPoints&, const HealthPoints&);
    friend bool operator==(const HealthPoints&, const HealthPoints&);
    friend std::ostream& operator<<(std::ostream&, const HealthPoints&);
};

HealthPoints operator+(const int, const HealthPoints&);
HealthPoints operator-(const int, const HealthPoints&);

bool operator!=(const HealthPoints&, const HealthPoints&);
bool operator<=(const HealthPoints&, const HealthPoints&);
bool operator>(const HealthPoints&, const HealthPoints&);
bool operator>=(const HealthPoints&, const HealthPoints&);

#endif