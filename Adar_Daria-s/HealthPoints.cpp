#include "HealthPoints.h"

HealthPoints::HealthPoints(const int points)
{
    if (points <= 0)
    {
        throw InvalidArgument(); // make sure someone catches it 
    }

    m_maxHealthPoints = points;
    m_healthPoints = points;
}

HealthPoints &HealthPoints::operator+=(const int number)
{
    // ask about this
    if (number < 0)
    {
        return *this -= (-number);
    }
    if (m_healthPoints + number >= m_maxHealthPoints)
    {
        m_healthPoints = m_maxHealthPoints;
        return *this;
    }
    m_healthPoints += number;
    return *this;
}

HealthPoints &HealthPoints::operator-=(const int number)
{
    if (number < 0)
    {
        return *this += (-number);
    }
    if (m_healthPoints - number <= 0)
    {
        m_healthPoints = 0;
        return *this;
    }
    m_healthPoints -= number;
    return *this;
}

HealthPoints HealthPoints::operator+(const int number) const
{
    // try to implement using +=
    if (number < 0)
    {
        return *this - (-number);
    }
    int inputHealthPoints = this->m_healthPoints + number;
    if (inputHealthPoints >= m_maxHealthPoints)
    {
        inputHealthPoints = m_maxHealthPoints;
    }
    HealthPoints newObject(m_maxHealthPoints);
    newObject.m_healthPoints = inputHealthPoints;
    return newObject;
}

HealthPoints operator+(int const number, const HealthPoints &object)
{
    return object + number;
}
HealthPoints HealthPoints::operator-(const int number) const
{
    //try to implement using -=
    if (number < 0)
    {
        return *this + (-number);
    }
    int inputHealthPoints = this->m_healthPoints - number;
    if (inputHealthPoints <= 0)
    {
        inputHealthPoints = 0;
    }
    HealthPoints newObject(m_maxHealthPoints);
    newObject.m_healthPoints = inputHealthPoints;
    return newObject;
}

HealthPoints operator-(int const number, const HealthPoints &object)
{
    return object - number;
}

ostream &operator<<(ostream &os, const HealthPoints &object)
{
    return os << object.m_healthPoints << "(" << object.m_maxHealthPoints << ")";
}

bool operator==(const HealthPoints &rightObject, const HealthPoints &leftObject)
{
    return rightObject.m_healthPoints == leftObject.m_healthPoints;
}
bool operator<(const HealthPoints &rightObject, const HealthPoints &leftObject)
{
    return rightObject.m_healthPoints < leftObject.m_healthPoints;
}

bool operator>(const HealthPoints &rightObject, const HealthPoints &leftObject)
{
    return leftObject < rightObject;
}
bool operator!=(const HealthPoints &rightObject, const HealthPoints &leftObject)
{
    return !(rightObject == leftObject);
}
bool operator<=(const HealthPoints &rightObject, const HealthPoints &leftObject)
{
    return !(leftObject < rightObject);
}
bool operator>=(const HealthPoints &rightObject, const HealthPoints &leftObject)
{
    return !(rightObject < leftObject);
}
