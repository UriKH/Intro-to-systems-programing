#pragma once

class CoinPile{
    int m_coins;

    static const int MIN_COINS = 0;

    friend bool operator<(const CoinPile&, const CoinPile&);
    friend bool operator==(const CoinPile&, const CoinPile&);
public:
    /**
     * Create a coin pile with given starting amount of coins
     *
     * @param coins a starting amount of coins
    */
    explicit CoinPile(int coins = MIN_COINS);

    CoinPile& operator+=(const int);
    CoinPile& operator-=(const int);
    operator int() const;
};

bool operator!=(const CoinPile&, const CoinPile&);
bool operator<=(const CoinPile&, const CoinPile&);
bool operator>(const CoinPile&, const CoinPile&);
bool operator>=(const CoinPile&, const CoinPile&);