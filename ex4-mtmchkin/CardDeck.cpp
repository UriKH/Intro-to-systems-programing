#include "CardDeck.h"
#include <memory>

void CardDeck::insertBack(std::shared_ptr<Card> card){
    m_cardDeck.push_back(std::move(card));
}

const std::shared_ptr<Card> CardDeck::drawCard(){
    return m_cardDeck.front();
}