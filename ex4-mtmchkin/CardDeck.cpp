#include "CardDeck.h"
#include <memory>
#include <iostream>

void CardDeck::insertBack(std::shared_ptr<Card> card){
    m_cardDeck.push(std::move(card));
}

const std::shared_ptr<Card> CardDeck::drawCard(){
    std::shared_ptr<Card> temp = m_cardDeck.front();
    m_cardDeck.pop();
    return temp;
}