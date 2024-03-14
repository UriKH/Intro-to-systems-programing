#ifndef HEALTH_POINTS_H
#define HEALTH_POINTS_H

#include <iostream>
using namespace std;

#define DEFAULT_POINTS 100

class HealthPoints
{

    int m_healthPoints;
    int m_maxHealthPoints;

public:
    class InvalidArgument
    {
    };

    // big three
    HealthPoints(int points = DEFAULT_POINTS);
    ~HealthPoints() = default;
    HealthPoints &operator=(const HealthPoints &other) = default;

    // arithmetics
    HealthPoints &operator+=(const int);
    HealthPoints &operator-=(const int);
    HealthPoints operator+(const int) const;
    HealthPoints operator-(const int) const;

    // friend methods
    friend bool operator==(const HealthPoints &, const HealthPoints &);
    friend bool operator<(const HealthPoints &, const HealthPoints &);

    friend ostream &operator<<(ostream &, const HealthPoints &);
};
// semetric arithmetics
HealthPoints operator+(int const, const HealthPoints &);
HealthPoints operator-(int const, const HealthPoints &);

// boolean functions
bool operator!=(const HealthPoints &, const HealthPoints &);
bool operator<=(const HealthPoints &, const HealthPoints &);
bool operator>=(const HealthPoints &, const HealthPoints &);
bool operator>(const HealthPoints &, const HealthPoints &);

#endif
