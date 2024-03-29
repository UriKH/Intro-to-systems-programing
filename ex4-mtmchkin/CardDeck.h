#pragma once

#include "Cards/Card.h"
#include <queue>
#include <memory>

//TODO

class CardDeck{
private:
    std::queue<std::unique_ptr<Card>> m_cardDeck;
public:
    void insertCard(std::unique_ptr<Card> card);
    std::unique_ptr<Card> drawCard();
};