#include "CoinPile.h"
#include <stdexcept>

CoinPile::CoinPile(int coins) : m_coins(coins){
    if (coins < MIN_COINS){
        throw std::invalid_argument("Starting coin amount must be positive");
    }
}

CoinPile::operator int() const{
    return m_coins;
}


CoinPile& CoinPile::operator+=(const int amount){
    m_coins += amount;
    if (m_coins < MIN_COINS){
        m_coins = MIN_COINS;
    }
    return *this;
}

CoinPile& CoinPile::operator -= (const int amount){
    *this += -amount;
    return *this;
}

bool operator==(const CoinPile& hp, const CoinPile& other){
    return hp.m_coins == other.m_coins;
}

bool operator!=(const CoinPile& hp, const CoinPile& other){
    return !(hp == other);
}

bool operator<(const CoinPile& hp, const CoinPile& other){
    return hp.m_coins < other.m_coins;
}

bool operator>(const CoinPile& pile, const CoinPile& other){
    return !(pile < other) && pile != other;
}

bool operator<=(const CoinPile& pile, const CoinPile& other){
    return !(pile > other);
}

bool operator>=(const CoinPile& pile, const CoinPile& other){
    return !(pile < other);
}
