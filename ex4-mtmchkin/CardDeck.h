#pragma once

#include "Cards/Card.h"
#include <deque>
#include <memory>

//TODO

class CardDeck{
private:
    std::deque<std::shared_ptr<Card>> m_cardDeck;
public:
    void insertBack(std::shared_ptr<Card> card);
    const std::shared_ptr<Card> drawCard();
};