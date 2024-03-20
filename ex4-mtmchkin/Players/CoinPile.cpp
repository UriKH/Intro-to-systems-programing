#include "CoinPile.h"

CoinPile::CoinPile(int coins) : m_coins(coins){
    if (coins < MIN_COINS){
        throw InvalidArgument();
    }
}

bool CoinPile::pay(int amount){
    if (amount < 0){
        throw InvalidArgument();
    }

    if (m_coins - amount < MIN_COINS){
        return false;
    }
    m_coins -= amount;
    return true;
}

void CoinPile::add(int amount){
    if (amount < 0){
        throw InvalidArgument();
    }
    m_coins += amount;
}

int CoinPile::getCoins() const{
    return m_coins;
}