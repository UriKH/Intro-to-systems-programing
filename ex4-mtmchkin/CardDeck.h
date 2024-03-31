#pragma once

#include "Cards/Card.h"
#include <queue>
#include <memory>

//TODO

class CardDeck{
private:
    std::queue<std::unique_ptr<Card>> m_cardDeck;
public:
    /**
     * Inserts the given card to the cards deck.
     * 
     * @param card the card.
     * 
     * @return void
    */
    void insertCard(std::unique_ptr<Card> card);

    /**
     * Returns the front card, then removes it from the cards deck.
     * 
     * @return the front card.
    */
    std::unique_ptr<Card> drawCard();
};