#include "CardDeck.h"
#include <memory>
#include <iostream>

void CardDeck::insertCard(std::unique_ptr<Card> card){
    m_cardDeck.push(std::move(card));
}

std::unique_ptr<Card> CardDeck::drawCard(){
    std::unique_ptr<Card> temp = std::move(m_cardDeck.front());
    m_cardDeck.pop();
    return temp;
}