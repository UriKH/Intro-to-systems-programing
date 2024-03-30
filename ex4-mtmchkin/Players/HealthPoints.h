#pragma once

class HealthPoints{
    int m_hp;
    int m_maxHP;

    static const int DEFUALT_MAX_HP = 100;

    friend bool operator<(const HealthPoints&, const HealthPoints&);
    friend bool operator==(const HealthPoints&, const HealthPoints&);
public:
    static const int MIN_HP = 0;

    /**
     * Create a healthpoints handler with given maximum HP
     *
     * @param maxHP maximum HP available
    */
    explicit HealthPoints(int maxHP = DEFUALT_MAX_HP);

    HealthPoints& operator+=(const int);
    HealthPoints& operator-=(const int);
    operator int() const;
};

bool operator!=(const HealthPoints&, const HealthPoints&);
bool operator<=(const HealthPoints&, const HealthPoints&);
bool operator>(const HealthPoints&, const HealthPoints&);
bool operator>=(const HealthPoints&, const HealthPoints&);