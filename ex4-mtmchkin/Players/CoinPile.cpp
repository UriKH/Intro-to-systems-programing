#include "CoinPile.h"
#include <stdexcept>

CoinPile::CoinPile(int coins) : m_coins(coins){
    if (coins < MIN_COINS){
        throw std::invalid_argument("Starting coin amount must be positive");
    }
}

bool CoinPile::pay(int amount){
    if (amount < 0){
        throw std::invalid_argument("Can not pay negative prices");
    }

    if (m_coins - amount < MIN_COINS){
        return false;
    }
    m_coins -= amount;
    return true;
}

void CoinPile::add(int amount){
    if (amount < 0){
        throw std::invalid_argument("Can not add negative amount");
    }
    m_coins += amount;
}

int CoinPile::getCoins() const{
    return m_coins;
}

CoinPile::operator int() const{
    return m_coins;
}