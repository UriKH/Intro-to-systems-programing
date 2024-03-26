#include "CardDeck.h"

void CardDeck::insertBack(const Card& card){
    m_cardDeck.push_back(std::make_unique<Card>(card));
}

Card& CardDeck::drawCard(){
    return *m_cardDeck.front();
}