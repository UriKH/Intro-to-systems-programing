#include "CardDeck.h"
#include <memory>

void CardDeck::insertBack(const Card& card){
    m_cardDeck.push_back(std::make_shared<Card>(card));
}

Card& CardDeck::drawCard(){
    return *m_cardDeck.front();
}