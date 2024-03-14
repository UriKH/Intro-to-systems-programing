#ifndef HEALTH_POINTS_H
#define HEALTH_POINTS_H

#include <iostream>

class HealthPoints{
public:
    // error classes
    class InvalidArgument{};

    HealthPoints(int hp = MAX_DEFAULT_HP);

    HealthPoints& operator+=(const int);
    HealthPoints& operator-=(const int);
    HealthPoints operator+(const int) const;
    HealthPoints operator-(const int) const;

private:
    int m_currentHp;
    int m_maxHp;

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