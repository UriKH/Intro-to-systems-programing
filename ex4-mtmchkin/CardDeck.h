#pragma once

#include "Card.h"
#include "Monsters.h"
#include <deque>
#include <memory>

class CardDeck{
private:
    std::deque<std::shared_ptr<Card>> m_cardDeck;
public:
    void insertBack(const Card& card);
    Card& drawCard();
};