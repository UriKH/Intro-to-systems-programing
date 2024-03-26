#pragma once

#include "Card.h"
#include "Gang.h"
#include "Giant.h"
#include "Dragon.h"
#include "Goblin.h"
#include <deque>
#include <memory>

class CardDeck{
private:
    std::deque<std::unique_ptr<Card>> m_cardDeck;
public:
    void insertBack(const Card& card);
    Card& drawCard();
};