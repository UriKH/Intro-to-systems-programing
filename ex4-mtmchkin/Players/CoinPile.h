#pragma once

class CoinPile{
    int m_coins;

    static const int MIN_COINS = 0;
public:
    explicit CoinPile(int coins = MIN_COINS);

    bool pay(int);
    void add(int);
    int getCoins() const;
};